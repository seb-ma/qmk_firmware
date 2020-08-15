/*
Copyright 2020 @GauthamYerroju @seb-ma

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "oled.h"
#if defined(OLED_DRIVER_ENABLE) && defined(RENDER_ANIMATIONS) && defined(STARFIELD_ANIMATION)
#include "lib/lib8tion/lib8tion.h"


#define MAX_STARS     24
#define ZOOM_SPEED    16
#define SPAWN_RANGE   16
#define SPAWN_DELAY   333

#define ANIM_FRAME_DURATION     100 // Duration of each frame
#define ANIM_FRAME_DURATION_MIN 50  // Minimal duration of each frame
#define ANIM_FRAME_DURATION_MAX 150 // Maximal duration of each frame

#define OLED_ANIM_STARFIELD_DUALLAYER

uint8_t n_stars = 0;
uint8_t star_ang[MAX_STARS];
uint8_t star_rad[MAX_STARS];
uint32_t star_spawn_timer = 0;

uint16_t center_x = OLED_DISPLAY_WIDTH / 2;
uint16_t center_y = OLED_DISPLAY_HEIGHT / 2;

#define COLLISION_MASK_LEFT  (1 << 3)
#define COLLISION_MASK_DOWN  (1 << 2)
#define COLLISION_MASK_UP    (1 << 1)
#define COLLISION_MASK_RIGHT (1 << 0)

uint8_t rect_out_of_bounds(int16_t x, int16_t y, uint8_t width, uint8_t height, int8_t padding) {
    /* Return a bit mask representing the direction collission happened.
     * Direction positions are like vim arrow keys: <left><down><up><right>
     */
    uint8_t collision_map = 0x00;
    if (x < -padding) {
        collision_map |= COLLISION_MASK_LEFT;
    }
    if ((x + width) >= (OLED_DISPLAY_WIDTH + padding)) {
        collision_map |= COLLISION_MASK_RIGHT;
    }
    if (y < -padding) {
        collision_map |= COLLISION_MASK_UP;
    }
    if ((y + height) >= (OLED_DISPLAY_HEIGHT + padding)) {
        collision_map |= COLLISION_MASK_DOWN;
    }
    return collision_map;
}

bool point_out_of_bounds(int16_t x, int16_t y, int8_t padding) {
    return rect_out_of_bounds(x, y, 1, 1, padding);
}

void starfield_render_init_frame(t_animation* animation) {
    center_x = random8_max(OLED_DISPLAY_WIDTH);
    center_y = random8_max(OLED_DISPLAY_HEIGHT);

    animation->start_timer = 0;
    animation->frame_duration = ANIM_FRAME_DURATION;
    // Dependant to WPM
    animation->ratioPerc = 0;
    animation->frame_duration_min = ANIM_FRAME_DURATION_MIN;
    animation->frame_duration_max = ANIM_FRAME_DURATION_MAX;
    // Base frame
    starfield_render_next_frame(animation);
}

void spawn_star(void) {
    star_ang[n_stars] = random8();
    star_rad[n_stars] = random8_max(16) + SPAWN_RANGE;
    n_stars++;
}

uint8_t get_star_x(uint8_t index) {
    return center_x + (cos8(star_ang[index]) - 128) * star_rad[index] / 128;
}

uint8_t get_star_y(uint8_t index) {
    return center_y + (sin8(star_ang[index]) - 128) * star_rad[index] / 128;
}

void update_star(uint8_t index) {
#ifdef OLED_ANIM_STARFIELD_DUALLAYER
    if (index % 2 == 0) {
        star_rad[index] += 1;
    } else
#endif
    {
        star_rad[index] += map8(cubicwave8(star_rad[index]), 1, ZOOM_SPEED);
    }
    if (rect_out_of_bounds(get_star_x(index), get_star_y(index), 1, 1, 24)) {
        star_ang[index] = random8_max(250) + 5;
        star_rad[index] = random8_max(16) + SPAWN_RANGE;
    }
}

void update_stars(void) {
    for(uint8_t i = 0; i < n_stars; i++) {
        update_star(i);
    }
}

void draw_stars(void) {
    uint8_t x, y;
    for(uint8_t i = 0; i < n_stars; i++) {
        x = get_star_x(i);
        y = get_star_y(i);
        if (!point_out_of_bounds(x, y, 0)) {
            oled_write_pixel(x, y, true);
        }
    }
}

void erase_stars(void) {
    uint8_t x, y;
    for(uint8_t i = 0; i < n_stars; i++) {
        x = get_star_x(i);
        y = get_star_y(i);
        if (!point_out_of_bounds(x, y, 0)) {
            oled_write_pixel(x, y, false);
        }
    }
}

void starfield_render_next_frame(t_animation* animation) {
    if ((n_stars < MAX_STARS) && (timer_elapsed32(star_spawn_timer) >= SPAWN_DELAY)) {
        spawn_star();
        star_spawn_timer = timer_read32();
    }

    animation->start_timer = timer_read32();
    erase_stars();
    update_stars();
    draw_stars();
}

#endif // defined(OLED_DRIVER_ENABLE) && defined(STARFIELD_ANIMATION)
