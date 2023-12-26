#ifndef OOPPROG3_AUX_FUNCS_H
#define OOPPROG3_AUX_FUNCS_H

#include <string>
#include <iostream>

namespace Prog3 {
    int input_num(std::istream& s, const char* msg, int range_first, int range_second, int& num);
    int input_string(std::istream& s, const char* msg, std::string& str);

    template <typename T>
    T* my_realloc(const T* arr, int prev_size, int size);
}

#endif