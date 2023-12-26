#ifndef OOPPROG3_TABLE_H
#define OOPPROG3_TABLE_H

#include <stdexcept>
#include <vector>
#include <iterator>
#include "../living/living.h"
#include "../apartment/apartment.h"
#include "../flat/flat.h"

using std::vector;

namespace Prog3{
    template <typename T>
    class TableIterator {
        using difference_type = std::ptrdiff_t;
        using element_type = T;
        using pointer = element_type *;
        using reference = element_type &;
        using iterator_category = std::forward_iterator_tag;
        private:
            pointer ptr, start, sentinel;
            static_assert(std::sentinel_for<decltype(sentinel), decltype(ptr));
        public:
            Iterator() { throw std::runtime_error("Not implemented"); }
            Iterator(pointer ptr, pointer sentinel) : ptr(ptr), start(ptr), sentinel(sentinel) {}
            reference operator*() const { return *ptr; }
            auto &operator++() { ptr++; return *this; }
            auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }
            auto operator<=>(const Iterator &) const = default;
            auto begin() {return start;}
            auto end() {return sentinel;}
    };

    struct Keyspace {
        Living* l = nullptr;
        int status = -1;
        int price = 0;
    };

    template <typename T>
    class Table{
        using Iterator = TableIterator<T>
        private:
            T* arr = nullptr;
            static_assert(std::forward_iterator<TableIterator>);
        public:
            Table() = default;
            Table(Living** arr, unsigned int len, int* status = nullptr, int* prices = nullptr);
            ~Table();

            Table &setLiving(Living** arr, unsigned int len);
            Table &setStatus(unsigned int ind, int status);
            Table &setPrice(unsigned int ind, int price);

            Living* getLiving(unsigned int ind) const;
            unsigned int getLen() const noexcept { return arr.size(); }
            int getStatus(unsigned int ind) const;
            int getPrice(unsigned int ind) const;
            vector<Keyspace>& getLivingArr() const noexcept { return (vector<Keyspace>&)arr; }

            Table &addLiving(Living* living, int status = 0, int price = 0);
            int findLiving(Address& addr) const;
            void findCheapest(int& apartment_ind, int& flat_ind) const;
            Table &removeLiving(unsigned int ind);

            friend ostream& operator << (ostream&, const Table&);
    };
}

#endif