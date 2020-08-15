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
