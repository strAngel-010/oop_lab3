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
            Table<Keyspace> table;
            Cottage* cottages = nullptr;
            int len = 0;
            
            int start_dialog(int& ans);
            int check_in();
            void check_out();
            void print_unsettled();
            void print_cheapest();
        public:
            App() = default;
            ~App();

            App& start();
    };

    Keyspace* keyspace_realloc(Keyspace* arr, int prev_size, int size);
}

#endif