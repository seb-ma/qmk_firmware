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

#include "generator.h"
#include "in_bongocat/bitmaps.h"

/*
Compilation: gcc generator.c gen_bongocat.c -o gen_bongocat
*/

int main(char* args, int nb) {
    const unsigned char empty[sizeof(up)] = {0};
    const unsigned char* up_arr[] = {up};
    const unsigned char* others[] = {empty, key1, key2, key3, key4, key5, key6};
    unsigned int size = sizeof(up);

    printf("/*--------------\n  Base (paws up)\n  --------------*/\n");
    GET_COMPARE(up,   others, "", "");

    printf("\n/*--------------\n  Left paw down\n  --------------*/\n");
    GET_COMPARE(key1, up_arr, "diff_", "_up");
    GET_COMPARE(key2, up_arr, "diff_", "_up");
    GET_COMPARE(key3, up_arr, "diff_", "_up");

    printf("\n/*--------------\n  Right paw down\n  --------------*/\n");
    GET_COMPARE(key4, up_arr, "diff_", "_up");
    GET_COMPARE(key5, up_arr, "diff_", "_up");
    GET_COMPARE(key6, up_arr, "diff_", "_up");
    return 0;
}
