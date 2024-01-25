#ifndef OOPPROG3_TABLE_H
#define OOPPROG3_TABLE_H
#define REALLOC_SIZE 5

#include <stdexcept>
#include <vector>
#include <iterator>
#include <thread>
#include <atomic>
#include "../living/living.h"
#include "../apartment/apartment.h"
#include "../flat/flat.h"
#include "../aux_funcs/aux_funcs.h"

using std::vector, std::endl, std::cout, std::jthread;

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
                    bool operator != (const TableIterator & it) const{ return ptr != it.ptr; }
                    auto operator=(const TableIterator &it) {
                        ptr = it.ptr;
                        start = it.start;
                        sentinel = it.sentinel;
                        return *this;
                    }
                    difference_type operator - (const TableIterator &it){ return ptr - it.ptr; }
                    auto begin() {return start;}
                    auto end() {return sentinel;}
            };

            using Iterator = TableIterator;
            static std::ptrdiff_t distance(Iterator first, Iterator last) {
                return last - first;
            }

            Table() = default;
            Table(Living** arr, unsigned int len, int* status = nullptr, int* prices = nullptr);
            ~Table();

            Table<T> &setLiving(Living** arr, unsigned int len);
            Table<T> &setStatus(unsigned int ind, int status);
            Table<T> &setPrice(unsigned int ind, int price);

            Living* getLiving(unsigned int ind) const;
            unsigned int getLen() const noexcept { return arr.size(); }
            int getStatus(unsigned int ind) const;
            int getPrice(unsigned int ind) const;
            T* getLivingArr() const noexcept { return arr; }

            Table<T> &addLiving(Living* living, int status = 0, int price = 0);
            int findLiving(Address& addr) const;
            void findCheapest(int& apartment_ind, int& flat_ind) const;
            void local_min(Iterator cur, Iterator end, int& local_apartment_ind, int& local_flat_ind);
            void findCheapest_mt(int& apartment_ind, int& flat_ind);
            Table<T> &removeLiving(unsigned int ind);
            Table<T> &erase();

            Iterator begin() const { return Iterator(arr, arr+len); }
            Iterator end() const { return Iterator(arr+len, arr+len); }

            friend ostream& operator << (ostream& s, const Table<T>& table){
                Iterator it;
                for (it = table.begin(); it != table.end(); ++it){
                    if (it->l) { s << *(it->l); }
                    else { throw std::runtime_error("No pointer to living"); }
                    switch (it->status){
                        case -1:
                            s << "No information about owners" << endl;
                            break;
                        case 0:
                            s << "No current owners" << endl;
                            break;
                        case 1:
                            s << "Living is owned" << endl;
                            break;
                        default: throw std::runtime_error("Wrong status information");
                    }
                    s << "Price per square meter: " << it->price << endl << endl;
                }
                return s;
            }

        private:
            T* arr = nullptr;
            int len = 0;
            int allocated_len = 0;
    };
    #include "table.tcc"
}

#endif