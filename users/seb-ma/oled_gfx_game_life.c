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
#include "oled.h"
#if defined(OLED_DRIVER_ENABLE) && defined(RENDER_ANIMATIONS) && defined(LIFE_ANIMATION)
#include "lib/lib8tion/lib8tion.h"

#define ANIM_FRAME_DURATION 500 // Duration of each frame

/*
Animation of "Conway's Game of Life"
Source : https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

Lots of rules exists and DotLife (B3/S023) is chosen here over Conway (B3/S23) because of its population stability over cycles.
Counterpart is that population is more important in average and display is more fuzzy.
It may be mitigate (a few) by using a universe with limits on borders instead of a toroidal universe.

Rules references:
- B3/S23: Standard (Conway) rule - https://conwaylife.com/wiki/Conway%27s_Game_of_Life
- B3/S023: DotLife rule - https://conwaylife.com/wiki/OCA:DotLife

Implementation:
- Implementation is done on a simple array instead of array of array to optimize processing
- This implementation of universe is a toroidal universe:
    - left and right of array are connected
    - up and down of array are connected
- Simplest implementation should use 2 universe (1 for current generation and 1 to prepare next generation),
    and for each cell, iterate all over the neighbors to count them.
    But, to reduce memory footprint, a slice of universe is used and the previous slice is displayed before going next iteration
    And to reduce cpy usage, neighbors are added to neighborhood only when cell is active (reduce 9-cells-iteration only to active cells)
*/

#define CELL_SIZE 3
#define NB_ROWS (OLED_DISPLAY_HEIGHT / 8 / CELL_SIZE) // divide by 8 to concatenate each bit by chars in rows
#define NB_COLS (OLED_DISPLAY_WIDTH / CELL_SIZE)

#define INIT_RATIO 15 // Percent of active cells at start of universe

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

/* Universe of the game of life */
static char universe[NB_ROWS * NB_COLS] = {0};

/* Write a cell to OLED */
static void write_cell_oled(const uint16_t x, const uint16_t y, const bool value) {
#if CELL_SIZE == 1
    oled_write_pixel(i, j, value);
#else
    for (uint8_t a = 0; a < CELL_SIZE; a++) {
        for (uint8_t b = 0; b < CELL_SIZE; b++) {
            oled_write_pixel(x * CELL_SIZE + a, y * CELL_SIZE + b, value);
        }
    }
#endif // CELL_SIZE value
}

/* Callback to render the first frame of the animation */
void gamelife_render_init_frame(t_animation* animation) {
    for (uint16_t i = 0; i < sizeof(universe); i++) {
        char value = 0;
        for (int8_t b = 0; b < 8; b++) {
            value |= (random8_max(100) < INIT_RATIO) << b;
        }
        universe[i] = value;
    }
    animation->start_timer = timer_read32();
    animation->frame_duration = ANIM_FRAME_DURATION;
    // Not dependant to WPM
    animation->ratioPerc = -1;
    animation->frame_duration_min = ANIM_FRAME_DURATION;
    animation->frame_duration_max = ANIM_FRAME_DURATION;
}

/* Callback to render the next frame of the animation */
void gamelife_render_next_frame(t_animation* animation) {
    animation->start_timer = timer_read32();
    // 3 rotating slice + first 2
    char tmp_slice_neighbors[5 * 8 * NB_ROWS] = {0};

    // For each column
    for (uint8_t j = 0; j < NB_COLS + 2; j++) {
        if (j < NB_COLS - 2) {
            memset8(&tmp_slice_neighbors[((j + 1) % 3) * 8 * NB_ROWS], 0, 8 * NB_ROWS);
        } else {
            // Restore tmp_slice_neighbors of j = NB_COLS - 1 and 0
            memcpy8(&tmp_slice_neighbors[((j + 1) % 3) * 8 * NB_ROWS], &tmp_slice_neighbors[(3 + NB_COLS - 2 - j) * 8 * NB_ROWS], 8 * NB_ROWS);
        }
        if (j < NB_COLS) {
            for (uint8_t i = 0; i < NB_ROWS; i++) {
                const char byte_cells = universe[((j + NB_COLS) % NB_COLS) * NB_ROWS + ((i + NB_ROWS) % NB_ROWS)];
                // For each row
                for (int8_t b = 0; b < 8; b++) {
                    // Cell is alive, increase neighborhood
                    if (1 & (byte_cells >> b)) {
                        for (int8_t jj = -1; jj < 2; jj++) {
                            for (int8_t ii = -1; ii < 2; ii++) {
                                tmp_slice_neighbors[((j + jj) % 3) * 8 * NB_ROWS + 8 * i + b + ii]++;
                            }
                        }
                        // Remove cell itself
                        tmp_slice_neighbors[(j % 3) * 8 * NB_ROWS + 8 * i + b]--;
                    }
                }
            }
        }

        if (j > 1) {
            // Update previous slice of universe
            for (uint8_t i = 0; i < NB_ROWS; i++) {
                char byte_cells = universe[((j - 1 + NB_COLS) % NB_COLS) * NB_ROWS + ((i + NB_ROWS) % NB_ROWS)];
                // For each row
                for (uint8_t b = 0; b < 8; b++) {
                    bool cell = 1 & (byte_cells >> b);
                    const uint8_t count = tmp_slice_neighbors[((j - 1) % 3) * 8 * NB_ROWS + 8 * i + b];

                    // Evolution of cell based on neighbors
                    if (cell && (count == 1 || count > 3)) {
                        // S23 + S0
                        // Survive if 2 or 3 neighbors (Conway rule) or 0 neighbour (DotLife rule)
                        //cell = 0;
                        write_cell_oled((j - 1) % NB_COLS, i * 8 + b, 0);
                        byte_cells &= ~(1 << b);
                    } else if (!cell && count == 3) {
                        // B3: A new cell is born (Conway and DotLife rule)
                        //cell = 1;
                        write_cell_oled((j - 1) % NB_COLS, i * 8 + b, 1);
                        byte_cells |= (1 << b);
                    }
                    // else: Cell remains the same
                }
                // Update universe and render to oled
                universe[((j - 1 + NB_COLS) % NB_COLS) * NB_ROWS + ((i + NB_ROWS) % NB_ROWS)] = byte_cells;
            }
        } else if (j <= 1) {
            // Save tmp_slice_neighbors of j = NB_COLS - 1 and 0
            memcpy8(&tmp_slice_neighbors[(3 + j) * 8 * NB_ROWS], &tmp_slice_neighbors[((j - 1) % 3) * 8 * NB_ROWS], 8 * NB_ROWS);
        }
    }
}

#endif // defined(OLED_DRIVER_ENABLE) && defined(LIFE_ANIMATION)
