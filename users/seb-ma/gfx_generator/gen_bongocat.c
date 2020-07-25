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
