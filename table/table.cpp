#include "table.h"

using std::vector;
using std::endl;

namespace Prog3 {
    Table::Table(Living** arr, unsigned int len, int* status, int* prices) {
        try {
            for (int i = 0; i < (int)len; ++i){
                Keyspace k;
                k.l = arr[i];
                
                if (status) { k.status = status[i]; }
                if (prices) { k.price = prices[i]; }
                this->arr.push_back(k);
            }
        } catch (...) { throw; }
    }

    Table::~Table(){
        std::vector<Keyspace>::iterator it;
        for (it = arr.begin(); it != arr.end(); ++it){
            delete it->l;
        }
        arr.clear();
    }

    Table &Table::setLiving(Living** arr, unsigned int len) {
        try {
            this->arr.clear();
            for (int i = 0; i < (int)len; ++i){
                Keyspace k;
                k.l = arr[i];
                this->arr.push_back(k); }
        } catch (...) { throw; }
        
        return *this;
    }

    Table &Table::setStatus(unsigned int ind, int status){
        if (status < -1 || status > 1){
            throw std::runtime_error("Wrong status (must be >=-1 && <= 1)");
        }
        
        if (ind >= arr.size()) {
            throw std::runtime_error("Wrong index");
        }

        try { this->arr[ind].status = status; }
        catch (...) { throw; }
        return *this;
    }

    Table &Table::setPrice(unsigned int ind, int price){
        if (ind >= arr.size()) {
            throw std::runtime_error("Wrong index");
        }

        try { arr[ind].price = price; }
        catch (...) { throw; }
        return *this;
    }

    Living* Table::getLiving(unsigned int ind) const {
        try{
            if (ind >= arr.size()) { throw std::runtime_error("Wrong index"); }
            return arr[ind].l;
        }
        catch (...) { throw; }
    }

    int Table::getStatus(unsigned int ind) const {
        if (ind >= arr.size()) { throw std::runtime_error("Wrong index"); }

        try { return arr[ind].status; }
        catch (...) { throw; }
    }

    int Table::getPrice(unsigned int ind) const {
        if (ind >= arr.size()) { throw std::runtime_error("Wrong index"); }

        try { return arr[ind].price; }
        catch (...) { throw; }
    }

    Table &Table::addLiving(Living* living, int status, int price){
        if (status < -1 || status > 1) { throw std::runtime_error("Wrong status"); }
        Keyspace k;
        k.l = living;
        k.status = status;
        k.price = price;
        arr.push_back(k);
        return *this;
    }

    int Table::findLiving(Address& addr) const {
        try{
            std::vector<Keyspace>::const_iterator it;
            Living* l;
            for (it = arr.begin(); it != arr.end(); ++it){
                l = it->l;
                if (l && l->getAddr() && *(l->getAddr()) == addr){
                    return std::distance(arr.begin(), it);
                }
            }
            return -1;
        } catch (...) { throw; }
    }

    void Table::findCheapest(int& apartment_ind, int& flat_ind) const{
        try{
            apartment_ind = -1;
            flat_ind = -1;
            std::vector<Keyspace>::const_iterator it;
            for (it = arr.begin(); it != arr.end(); ++it){
                if (dynamic_cast<Apartment*>(it->l)){
                    if (apartment_ind == -1) { 
                        apartment_ind = std::distance(arr.begin(), it);
                    }
                    if (arr[apartment_ind].price < it->price) { 
                        apartment_ind = std::distance(arr.begin(), it);
                    }
                } else {
                    if (flat_ind == -1) { 
                        flat_ind = std::distance(arr.begin(), it);
                    }
                    if (arr[flat_ind].price < it->price) { 
                        flat_ind = std::distance(arr.begin(), it);
                    }
                }
            }
        } catch (...) { throw; }
    }

    Table &Table::removeLiving(unsigned int ind){
        if (ind >= arr.size()) { throw std::runtime_error("Wrong index"); }

        try{
            delete arr[ind].l;
            arr[ind] = arr[arr.size()-1];
            arr.pop_back();
        } catch (...) { throw; }
        return *this;
    }

    ostream& operator << (ostream& s, const Table& table){
        vector<Keyspace>::iterator it;
        vector<Keyspace>& arr = table.getLivingArr();
        for (it = arr.begin(); it != arr.end(); ++it){
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
}