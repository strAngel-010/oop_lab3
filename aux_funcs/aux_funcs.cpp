#include "aux_funcs.h"

namespace Prog3{
    int input_num(std::string msg, int range_first, int range_second, int& num){
        while (true) {
            if (!msg.empty()) { cout << msg << endl; }
            cin >> num;
            if (cin.eof()) { return 1; }
            if (cin.bad()) { throw std::runtime_error("Input broken"); }
            if (cin.good()){
                if (num < range_first || num > range_second){
                    cout << "Wrong number, please repeat" << endl;
                } else { return 0; }
            }
        }
    }

    int input_string(std::string msg, std::string& str){
        if (!msg.empty()) { cout << msg << endl; }
        cin >> str;
        if (cin.eof()) { return 1; }
        if (cin.bad()) { throw std::runtime_error("Input broken"); }
        return 0;
    }
}