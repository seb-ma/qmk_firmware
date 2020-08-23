/*
Copyright 2020 @seb-ma

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
#include "oled_follower.h"
#if defined(OLED_DRIVER_ENABLE) && defined(RENDER_ANIMATIONS) && defined(POMODORO_ANIMATION)
#include "lib/lib8tion/lib8tion.h"

#define ANIM_FRAME_DURATION 250 // Duration of each frame

/*
Animation to render the remaining time of a pomodoro timer
The amount of pixels on are a representation of the remaining time.
Pixels are randomly switched off according to time.
*/

/* To have pixels removed by column (like skyline shadow) */
#define POMODORO_FALLING_RENDER


#define CELL_SIZE 2
#define NB_ROWS (OLED_DISPLAY_HEIGHT / 8 / CELL_SIZE)
#define NB_COLS (OLED_DISPLAY_WIDTH / CELL_SIZE)

// Map structure of characters on OLED: this is vertical with 1 bit per pixel
/*
      char 1     char 2     char 3     …   char 127
┌───┬──────────┬──────────┬──────────┬───┬────────────┐
│   │ p1_c1_b0 │ p1_c2_b0 │ p1_c3_b0 │ … │ p1_c128_b0 │
│ P │ p1_c1_b1 │ p1_c2_b1 │ p1_c3_b1 │ … │ p1_c128_b1 │
│ A │ p1_c1_b2 │ p1_c2_b2 │ p1_c3_b2 │ … │ p1_c128_b2 │
│ G │ p1_c1_b3 │ p1_c2_b3 │ p1_c3_b3 │ … │ p1_c128_b3 │
│ E │ p1_c1_b4 │ p1_c2_b4 │ p1_c3_b4 │ … │ p1_c128_b4 │
│   │ p1_c1_b5 │ p1_c2_b5 │ p1_c3_b5 │ … │ p1_c128_b5 │
│ 1 │ p1_c1_b6 │ p1_c2_b6 │ p1_c3_b6 │ … │ p1_c128_b6 │
│   │ p1_c1_b7 │ p1_c2_b7 │ p1_c3_b7 │ … │ p1_c128_b7 │
├───┼──────────┼──────────┼──────────┼───┼────────────┤
│ … │          │          │          │   │            │
├───┼──────────┼──────────┼──────────┼───┼────────────┤
│   │ p7_c1_b0 │ p7_c2_b0 │ p7_c3_b0 │ … │ p7_c128_b0 │
│ P │ p7_c1_b1 │ p7_c2_b1 │ p7_c3_b1 │ … │ p7_c128_b1 │
│ A │ p7_c1_b2 │ p7_c2_b2 │ p7_c3_b2 │ … │ p7_c128_b2 │
│ G │ p7_c1_b3 │ p7_c2_b3 │ p7_c3_b3 │ … │ p7_c128_b3 │
│ E │ p7_c1_b4 │ p7_c2_b4 │ p7_c3_b4 │ … │ p7_c128_b4 │
│   │ p7_c1_b5 │ p7_c2_b5 │ p7_c3_b5 │ … │ p7_c128_b5 │
│ 7 │ p7_c1_b6 │ p7_c2_b6 │ p7_c3_b6 │ … │ p7_c128_b6 │
│   │ p7_c1_b7 │ p7_c2_b7 │ p7_c3_b7 │ … │ p7_c128_b7 │
└───┴──────────┴──────────┴──────────┴───┴────────────┘
      char 1021  char 1022  char 1023  …   char 1024

*/

#if (MAX_SHARED_ANIMATION_BUFFER < (NB_ROWS * NB_COLS))
#   error "Size of shared_oled_buffer is too low"
#endif

/* Representation of pomodoro (each pixel is a slot of time) */
static char* const screen = shared_animation_buffer;
/* Number of pixels still activated on screen */
static uint32_t nb_cells_remaining = 8L * NB_ROWS * NB_COLS;

/* Write a column of cell to OLED */
static void write_cell_oled(const uint8_t x, const uint8_t y, const bool value) {
#if CELL_SIZE == 1
    oled_write_pixel(x, y, value);
#else
    for (uint8_t a = 0; a < CELL_SIZE; a++) {
        for (uint8_t b = 0; b < CELL_SIZE; b++) {
            oled_write_pixel(x + a, y + b, value);
        }
    }
#endif // CELL_SIZE value
}

/* Callback to render the first frame of the animation */
void pomodoro_render_init_frame(t_animation* animation) {
    animation->frame_duration = ANIM_FRAME_DURATION;
    // Not dependant to WPM
    animation->ratioPerc = -1;
    animation->frame_duration_min = ANIM_FRAME_DURATION;
    animation->frame_duration_max = ANIM_FRAME_DURATION;

    memset8(screen, 0xff, NB_ROWS * NB_COLS);
    nb_cells_remaining = 8L * NB_ROWS * NB_COLS;
    for (uint16_t i = 0; i < OLED_MATRIX_SIZE; i++) {
        oled_write_raw_byte(0xff, i);
    }
}

#define NB_MS_BY_CELL ((POMODORO_TIMER * 60L * 1000) / (8L * NB_ROWS * NB_COLS))
extern uint32_t pomodoro_start_timer;

/* Callback to render the next frame of the animation */
bool pomodoro_render_next_frame(t_animation* animation) {
    if (pomodoro_start_timer != 0) {
        const uint32_t time_elapsed = timer_elapsed32(pomodoro_start_timer);
        // Number of cells to fill to represent the remaining time in pomodoro
        const uint32_t nb_cells = MAX(0, (POMODORO_TIMER * 60L * 1000 - time_elapsed) / NB_MS_BY_CELL);

        // Remove pixels according to elapsed time at a random position
        while (nb_cells_remaining > nb_cells) {
#ifdef POMODORO_FALLING_RENDER
            const uint8_t start_col = random8_max(NB_COLS);
            bool found = false;
            for (uint8_t i = start_col; i < start_col + NB_COLS && !found; i++) {
                for (uint8_t j = 0; j < NB_ROWS && !found; j++) {
                    uint16_t index = (i % NB_COLS) * NB_ROWS + j;
                    uint8_t value = screen[index];
                    if (value != 0x00) {
                        for (uint8_t b = 0; b < 8; b++) {
                            if (1 & (value >> (b % 8))) {
                                value &= ~(1 << (b % 8));
                                nb_cells_remaining--;
                                write_cell_oled((i % NB_COLS) * CELL_SIZE, (j * 8 + b) * CELL_SIZE, false);
                                screen[index] = value;
                                break;
                            }
                        }
                        found = true;
                    }
                }
            }
#else // POMODORO_FALLING_RENDER
            uint16_t start = random16_max(NB_ROWS * NB_COLS);
            for (uint16_t i = start; i < start + (NB_ROWS * NB_COLS); i++) {
                uint16_t index = i % (NB_ROWS * NB_COLS);
                uint8_t value = screen[index];
                if (value != 0x00) {
                    for (uint8_t b = random8_max(8); b < 16; b++) {
                        if (1 & (value >> (b % 8))) {
                            value &= ~(1 << (b % 8));
                            nb_cells_remaining--;
                            write_cell_oled((index % NB_COLS) * CELL_SIZE, ((index / NB_COLS) * 8 + (b % 8)) * CELL_SIZE, false);
                            screen[index] = value;
                            break;
                        }
                    }
                    break;
                }
            }
#endif // POMODORO_FALLING_RENDER
        }
        return true;
    }
    return false;
}

#endif // defined(OLED_DRIVER_ENABLE) && defined(POMODORO_ANIMATION)
