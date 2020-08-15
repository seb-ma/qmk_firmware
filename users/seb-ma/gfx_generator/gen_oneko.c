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
#include "in_oneko/bitmaps.h"

/*
Compilation: gcc generator.c gen_oneko.c -o gen_oneko
*/

#define GET_COMPARE_EMPTY(x) get_compare(x, sizeof(x), empty_arr, sizeof(empty_arr) / sizeof(const char*), #x)

int main(char* args, int nb) {
    const unsigned char empty[sizeof(awake)] = {0};
    const unsigned char* empty_arr [] = {empty};
    const unsigned char* mati2_arr [] = {mati2};
    const unsigned char* kaki1_arr [] = {kaki1};
    const unsigned char* sleep1_arr[] = {sleep1};
    const unsigned char* dtogi1_arr[] = {dtogi1};
    const unsigned char* utogi1_arr[] = {utogi1};
    const unsigned char* ltogi1_arr[] = {ltogi1};

    // Actions
    printf("/*--------------\n  Actions\n  --------------*/\n");
    GET_COMPARE_EMPTY(mati2);
    GET_COMPARE_NO_APPEND(mati3, mati2_arr);
    GET_COMPARE_NO_APPEND(awake, mati2_arr);
    GET_COMPARE_NO_APPEND(jare2, mati2_arr);
    GET_COMPARE_EMPTY(kaki1);
    GET_COMPARE_NO_APPEND(kaki2, kaki1_arr);

    GET_COMPARE_EMPTY(sleep1);
    GET_COMPARE_NO_APPEND(sleep2, sleep1_arr);

    GET_COMPARE_EMPTY(ltogi1);
    GET_COMPARE_NO_APPEND(ltogi2, ltogi1_arr);
    GET_COMPARE_EMPTY(dtogi1);
    GET_COMPARE_EMPTY(utogi1);

    // Moves
    printf("\n/*--------------\n  Moves\n  --------------*/\n");
    GET_COMPARE_EMPTY(up1);
    GET_COMPARE_EMPTY(up2);
    GET_COMPARE_EMPTY(down1);
    GET_COMPARE_EMPTY(down2);
    GET_COMPARE_EMPTY(left1);
    GET_COMPARE_EMPTY(left2);
    GET_COMPARE_EMPTY(upleft1);
    GET_COMPARE_EMPTY(upleft2);
    GET_COMPARE_EMPTY(dwleft1);
    GET_COMPARE_EMPTY(dwleft2);

    // Right sprites are symmetrical to left ones
    //GET_COMPARE_EMPTY(rtogi1);   // Symmetrical of ltogi1
    //GET_COMPARE(rtogi2, rtogi1_arr, "", "_rtogi1"); // Symmetrical of ltogi2
    //GET_COMPARE_EMPTY(right1);   // Symmetrical of left1
    //GET_COMPARE_EMPTY(right2);   // Symmetrical of left2
    //GET_COMPARE_EMPTY(upright1); // Symmetrical of upleft1
    //GET_COMPARE_EMPTY(upright2); // Symmetrical of upleft2
    //GET_COMPARE_EMPTY(dwright1); // Symmetrical of dwleft1
    //GET_COMPARE_EMPTY(dwright2); // Symmetrical of dwleft2

    // Symmetrical between sprite #1 and #2
    //GET_COMPARE(dtogi2, dtogi1_arr, "", "_dtogi1"); // Symmetrical of dtogi1
    //GET_COMPARE(utogi2, utogi1_arr, "", "_utogi1"); // Symmetrical of utogi1

    return 0;
}
