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
#include <stdio.h>
#include <limits.h>

#include "generator.h"

int get_diff(const unsigned char ref[], long unsigned int size, const unsigned char* others[], long unsigned int nb_others, char* name, int type, int last_idx_modif) {
    int last_idx_modif_comp = 0;
    if (type == data_diff_index_delta) {
        printf("static const uint8_t %s_idx_delta[] PROGMEM = {", name);
    } else if (type == data_diff_size) {
        printf("static const uint8_t %s_siz[] PROGMEM = {", name);
    } else if (type == data_diff_values) {
        printf("static const char %s_val[] PROGMEM = {", name);
    }

    unsigned char mod = 10;
    unsigned int cmpt = 0;
    unsigned int nb_successive_modif = 0;
    unsigned int last_index = 0;
    unsigned int bound = size;
    if (last_idx_modif > 0 && last_idx_modif + 2 < size) {
        bound = last_idx_modif + 2;
    }
    for (unsigned int i = 0; i < bound; i++) {
        unsigned char was_last_successive = 1;
        for (unsigned int o = 0; o < nb_others; o++) {
            if ((ref[i] != others[o][i] && nb_successive_modif < UCHAR_MAX)
            // Avoid creating a new index if only 1 char is identical but previous and next are different
            || (nb_successive_modif > 0 && i < bound - 2 && ref[i + 1] != others[o][i + 1] && nb_successive_modif + 1 < UCHAR_MAX)) {
                was_last_successive = 0;
                ++nb_successive_modif;

                if (type == data_diff_values) {
                    if ((cmpt % mod) == 0) {
                        printf("\n    ");
                    }
                    ++cmpt;
                    printf("0x%02hhx, ", (unsigned char) ref[i]);
                }
                last_idx_modif_comp = i;
                break;
            }
        }

        // Stop also at limit of size or limit of delta in indexes
        if (nb_successive_modif != 0
              && ((i == size - 1) || (was_last_successive == 1))
            || (i - last_index == UCHAR_MAX))
         {
            if (type == data_diff_index_delta || type == data_diff_size) {
                if ((cmpt % mod) == 0) {
                    printf("\n    ");
                }
                ++cmpt;
                if (type == data_diff_index_delta) {
                    printf("% 3u, ", (i - nb_successive_modif) - last_index);
                } else if (type == data_diff_size) {
                    printf("% 3u, ", nb_successive_modif);
                }
                last_index = i - nb_successive_modif;
            }
            nb_successive_modif = 0;
        }
    }
    if (type != get_max_only) {
        printf("\n};\n\n");
    }
    return last_idx_modif_comp;
}

void get_compare(const unsigned char ref[], long unsigned int size, const unsigned char* others[], long unsigned int nb_others, char* name) {
    printf("// %s\n", name);
    int last_idx_modif = get_diff(ref, size, others, nb_others, "", get_max_only, -1);
    get_diff(ref, size, others, nb_others, name, data_diff_index_delta, last_idx_modif);
    get_diff(ref, size, others, nb_others, name, data_diff_size, last_idx_modif);
    get_diff(ref, size, others, nb_others, name, data_diff_values, last_idx_modif);
}
