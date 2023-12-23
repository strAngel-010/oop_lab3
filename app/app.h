#ifndef OOPPROG3_APP_H
#define OOPPROG3_APP_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include "../table/table.h"
#include "../cottage/cottage.h"
#include "../aux_funcs/aux_funcs.h"

namespace Prog3{
    class App {
        private:
            Table table;
            Cottage* cottages = nullptr;
            int len = 0;
        public:
            App() = default;
            ~App();

            App& start();
            int start_dialog(int& ans);
            int check_in(Table& table, Cottage** arr, int& len);
            void check_out(Table& table);
            void print_unsettled(Table& table);
            void print_cheapest(Table& table);
    };
}

#endif