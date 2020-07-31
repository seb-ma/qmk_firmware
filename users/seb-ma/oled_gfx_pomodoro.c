#include "oled.h"
#if defined(OLED_DRIVER_ENABLE) && defined(RENDER_ANIMATIONS) && defined(POMODORO_ANIMATION)
#include <string.h>

#define ANIM_FRAME_DURATION 1000 // Duration of each frame

/*
Animation to render the remaining time of a pomodoro timer
The amount of pixels on are a representation of the remaining time.
Pixels are randomly switched off according to time.
*/

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

/* Representation of pomodoro (each pixel is a slot of time) */
static char screen[NB_ROWS * NB_COLS] = {0xff};
/* Number of pixels still activated on screen */
static uint32_t nb_pixels_remaining = 8L * NB_ROWS * NB_COLS;

/* Write a char of cells to OLED
Similar function to the one in oled_gfx_game_life but as it is dependant to CELL_SIZE that may not be equals, need to be redefined
*/
static void write_char_cells_oled(const char value, const uint16_t i, const uint16_t j) {
#if CELL_SIZE == 1
    oled_write_raw_byte(value, i * OLED_DISPLAY_WIDTH + j);
#elif CELL_SIZE <= 4
    uint32_t val32 = 0;
    for (uint8_t b = 0; b < 8; b++) {
        bool pix = 1 & (value >> b);
        uint8_t pixVal = 0;
        for (uint8_t size = 0; size < CELL_SIZE; size++) {
            pixVal = pixVal << 1 | pix;
        }
        val32 = val32 << CELL_SIZE | pixVal;
    }
    for (uint8_t a = 0; a < CELL_SIZE; a++) {
        for (uint8_t b = 0; b < CELL_SIZE; b++) {
            oled_write_raw_byte(((char*)&val32)[a], (CELL_SIZE * i + a) * OLED_DISPLAY_WIDTH + CELL_SIZE * j + b);
        }
    }
#else // CELL_SIZE value
    #error Algorithm must be defined for defined CELL_SIZE value
#endif // CELL_SIZE value
}

/* Callback to render the first frame of the animation */
void pomodoro_render_init_frame(t_animation* animation) {
    animation->frame_duration = ANIM_FRAME_DURATION;
    // Not dependant to WPM
    animation->ratioPerc = -1;
    memset(screen, 0xff, NB_ROWS * NB_COLS);
    nb_pixels_remaining = 8L * NB_ROWS * NB_COLS;
    for (uint16_t i = 0; i < OLED_MATRIX_SIZE; i++) {
        oled_write_raw_byte(0xff, i);
    }
    animation->start_timer = timer_read32();
}

#define NB_MS_BY_PIXEL ((POMODORO_TIMER * 60L * 1000) / (8L * NB_ROWS * NB_COLS));
extern uint32_t pomodoro_start_timer;

/* Callback to render the next frame of the animation */
void pomodoro_render_next_frame(t_animation* animation) {
    if (pomodoro_start_timer != 0) {
        animation->start_timer = timer_read32();

        const uint32_t time_elapsed = timer_elapsed32(pomodoro_start_timer);
        if (time_elapsed < POMODORO_TIMER * 60L * 1000) {
            // Number of pixels to fill to represent the remaining time in pomodoro
            int32_t nbPix = (POMODORO_TIMER * 60L * 1000 - time_elapsed) / NB_MS_BY_PIXEL;

            // Remove pixels according to elapsed time at a random position
            while (nb_pixels_remaining > nbPix) {
                uint16_t start = rand() % (NB_ROWS * NB_COLS);
                for (uint16_t i = 0; i < NB_ROWS * NB_COLS; i++) {
                    uint16_t index = (i + start) % (NB_ROWS * NB_COLS);
                    uint8_t value = screen[index];
                    if (value != 0x00) {
                        for (uint8_t b = rand() % 8; b < 16 && value != 0; b++) {
                            if (1 & (value >> b % 8)) {
                                value &= ~(1 << b % 8);
                                nb_pixels_remaining--;
                                break;
                            }
                        }
                        screen[index] = value;
                        write_char_cells_oled(value, index / NB_COLS, index % NB_COLS);
                        break;
                    }
                }
            }
        }
    }
}

#endif // defined(OLED_DRIVER_ENABLE) && defined(POMODORO_ANIMATION)
