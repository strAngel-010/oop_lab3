#ifndef OOPPROG3_TABLE_H
#define OOPPROG3_TABLE_H

#include <stdexcept>
#include <vector>
#include "../living/living.h"

namespace Prog3{
    struct Keyspace {
        Living* l = nullptr;
        int status = -1;
        int price = 0;
    };

    class Table{
        private:
            std::vector<Keyspace> arr;
        public:
            Table() = default;
            Table(Living** arr, unsigned int len, int* status = nullptr, int* prices = nullptr);
            ~Table();

            Table &setLiving(Living** arr, unsigned int len);
            Table &setStatusArr(int* status, unsigned int len);
            Table &setStatus(unsigned int ind, int status);
            Table &setPrice(unsigned int ind, int price);
            Table &setPricesArr(int* prices, unsigned int len);

            Living* getLiving(unsigned int ind) const;
            unsigned int getLen() const noexcept { return arr.size(); }
            int getStatus(unsigned int ind) const;
            int getPrice(unsigned int ind) const;

            Table &addLiving(Living* living, int status = 0, int price = 0);
            int findLiving(Address& addr) const;
            Table &removeLiving(unsigned int ind);

            //ToDo: table output
    };
}

#endif