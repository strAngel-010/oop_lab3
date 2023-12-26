#ifndef OOPPROG3_TABLE_H
#define OOPPROG3_TABLE_H
#define REALLOC_SIZE 5

#include <stdexcept>
#include <vector>
#include <iterator>
#include "../living/living.h"
#include "../apartment/apartment.h"
#include "../flat/flat.h"
#include "../aux_funcs/aux_funcs.h"

using std::vector;

namespace Prog3{
    struct Keyspace {
        Living* l = nullptr;
        int status = -1;
        int price = 0;
    };

    template <typename T>
    class Table{
        public:
            class TableIterator {
                using difference_type = std::ptrdiff_t;
                using element_type = T;
                using pointer = element_type *;
                using reference = element_type &;
                using iterator_category = std::forward_iterator_tag;
                private:
                    pointer ptr, start, sentinel;
                    static_assert(std::sentinel_for<decltype(sentinel), decltype(ptr)>);
                public:
                    TableIterator() : ptr(nullptr), start(nullptr), sentinel(nullptr) {};
                    TableIterator(pointer ptr, pointer sentinel) : ptr(ptr), start(ptr), sentinel(sentinel) {};
                    reference operator*() const { return *ptr; }
                    pointer operator -> () const { return ptr; }
                    auto &operator++() { ptr++; return *this; }
                    auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }
                    auto operator<=>(const TableIterator &) const = default;
                    auto operator = (const TableIterator &it){ 
                        ptr = it.ptr; 
                        start = it.start;
                        sentinel = it.sentinel;
                    };
                    difference_type operator - (const TableIterator &it){ return ptr - it.ptr; }
                    auto begin() {return start;}
                    auto end() {return sentinel;}
            };

            using Iterator = TableIterator;
            typename std::ptrdiff_t distance(Iterator first, Iterator last) { return last - first; }

            Table() = default;
            Table(Living** arr, unsigned int len, int* status = nullptr, int* prices = nullptr);
            ~Table();

            Table &setLiving(T* arr, unsigned int len);
            Table &setStatus(unsigned int ind, int status);
            Table &setPrice(unsigned int ind, int price);

            Living* getLiving(unsigned int ind) const;
            unsigned int getLen() const noexcept { return arr.size(); }
            int getStatus(unsigned int ind) const;
            int getPrice(unsigned int ind) const;
            T* getLivingArr() const noexcept { return arr; }

            Table &addLiving(Living* living, int status = 0, int price = 0);
            int findLiving(Address& addr) const;
            void findCheapest(int& apartment_ind, int& flat_ind) const;
            Table &removeLiving(unsigned int ind);

            Iterator begin() const { return Iterator(arr, arr+len); }
            Iterator end() const { return Iterator(arr+len, arr+len); }

            friend ostream& operator << (ostream&, const Table<Keyspace>&);

        private:
            T* arr = nullptr;
            int len = 0;
            int allocated_len = 0;
            //static_assert(std::forward_iterator<TableIterator>);
    };
}

#endif