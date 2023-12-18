#include "aux_funcs.h"

using std::cout, std::endl;

namespace Prog3{
    int input_num(std::istream& s, const char* msg, int range_first, int range_second, int& num){
        while (true) {
            if (msg) { cout << msg << endl; }
            s >> num;
            if (s.eof()) { return 1; }
            if (s.bad()) { throw std::runtime_error("Input broken"); }
            if (s.good()){
                if (num < range_first || num > range_second){
                    cout << "Wrong number, please repeat" << endl;
                } else { return 0; }
            }
        }
    }

    int input_string(std::istream& s, const char* msg, std::string& str){
        if (msg) { cout << msg << endl; }
        s >> str;
        if (s.eof()) { return 1; }
        if (s.bad()) { throw std::runtime_error("Input broken"); }
        return 0;
    }

    //ToDo: add template realloc
}