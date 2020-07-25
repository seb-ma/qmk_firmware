#pragma once

enum data_type {
    data_diff_index_delta = 0,
    data_diff_size,
    data_diff_values,
    get_max_only
};

#define GET_COMPARE(x, y, pre, suf) get_compare(x, sizeof(x), y, sizeof(y) / sizeof(const char*), pre #x suf)
#define GET_COMPARE_NO_APPEND(x, y) get_compare(x, sizeof(x), y, sizeof(y) / sizeof(const char*), #x)

void get_compare(const unsigned char ref[], long unsigned int size, const unsigned char* others[], long unsigned int nb_others, char* name);
