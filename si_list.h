#ifndef __LIST_H
#define __LIST_H

#include <assert.h>
#include <stddef.h>
#include <alloc.h>
#include <si_iterator.h>
#include <si_algol.h>
#include <si_traits.h>
#include <si_vector.h>

template<typename T>
struct node{
    T val;
    node* pre;
    node* next;
    typedef node self;
    node() : pre(NULL), next(NULL){}
    node(T a) : val(a), pre(NULL), next(NULL){}
};


template<typename T, typename Alloc = simple_alloc>
class list{
public:
    // definition for list<T>::iterator
    struct iterator : public __Iterator_Template<node<T>, BidirectionalIterator>{
        typedef iterator self;
        pointer it;
        self& operator++() {
            assert(it);
            it = it->next;
            return *this;
        }
        self operator++(int) {
            self tmp = *this;
            ++it;
            return tmp;
        }
        self& operator--() {
            assert(it);
            it = it->pre;
            return *this;
        }
        self operator--(int) {
            self tmp = *this;
            --it;
            return tmp;
        }
        self operator+(int step) {
            self tmp = *this;
            if (step < 0)
                return tmp - (-step);
            for (int i = 0; i < step; ++i)
                ++tmp;
            return tmp;
        }
        self operator-(int step) {
            self tmp = *this;
            if (step < 0)
                return tmp - (-step);
            for (int i = 0; i < step; ++i)
                --tmp;
            return tmp;
        }
        bool operator==(const self& that) const {
            return it == that.it;
        }
        bool operator!=(const self& that) const {
            return it != that.it;
        }
        reference operator*() const {
            return (*it).val;
        }
        pointer operator->() const {
            return &(operator* ());
        }
        iterator(pointer = NULL) {
            it = pointer;
        }
    };
    // definition for list<T>
    // construct from vector, extend another list(no copy)
    // push_back, pop_back, insert, remove, size, begin, end
    size_t size() const {
        return length;
    }
    list() {
        length = 0;
        node<T>* end = new node<T>;
        node<T>* begin = new node<T>;
        begin->next = end;
        end->pre = begin;
        __begin = new iterator(begin);
        __end = new iterator(end);
        
    }
    list(const vector<T>& initial) {
        list();
        for (int i = 0; i < initial.size(); ++i)

    }
    iterator begin() const {
        return __begin + 1;
    }
    iterator end() const {
        return __end;
    }
    void insert(const size_t pos, const T val) {
        assert(pos >=0 && pos <= length);
        node<T>* tmp = new node<T>(val);
        iterator it_pos_minus1 = __begin + pos;
        iterator it_pos = it_pos_minus1 + 1;
        it_pos_minus1->next = tmp;
        tmp->pre = it_pos_minus1;
        tmp->next = it_pos;
        it_pos->pre = tmp;
        ++length;
    }
    void remove(const size_t pos) {
        assert(pos >=0 && pos < length);
        iterator it_pos_minus1 = __begin + pos;
        iterator it_pos = it_pos_minus1 + 1
        iterator it_pos_add1 = it_pos + 1;
        delete it_pos.it;
        it_pos_minus1->next = it_pos_add1;
        it_pos_add1->pre = it_pos_minus1;
        --length;
    }
    void push_back(const T val) {
        insert(length, val);
    }
    void pop_back(const T val) {
        remove(length-1);
    }
private:
    // head node
    iterator __begin;
    // node after tail node
    iterator __end;
    size_t length;
}