#ifndef __LIST_H
#define __LIST_H

#include <assert.h>
#include <stddef.h>
#include "si_alloc.h"
#include "si_iterator.h"
#include "si_algo.h"
#include "si_traits.h"
#include "si_vector.h"

template<typename T>
struct node{
    T val;
    node* pre;
    node* next;
    node() : pre(NULL), next(NULL){}
    node(T a) : val(a), pre(NULL), next(NULL){}
};

namespace si{
template<typename T, typename Alloc = simple_alloc>
class list{
public:
    // definition for list<T>::iterator
    struct iterator : public __Iterator_Template<node<T>, BidirectionalIterator> {
        typedef node<T> node_type;
        typedef node<T>* pointer;
        typedef node<T>& reference;
        typedef T value_type;
        typedef value_type* v_pointer;
        typedef value_type& v_reference;
        typedef typename __Iterator_Template<node<T>, BidirectionalIterator>::category category;
        typedef iterator self;
        pointer it;
        self& operator++() {
            assert(it);
            it = it->next;
            return *this;
        }
        self operator++(int) {
            self tmp = *this;
            ++(*this);
            return tmp;
        }
        self& operator--() {
            assert(it);
            it = it->pre;
            return *this;
        }
        self operator--(int) {
            self tmp = *this;
            --(*this);
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
        v_reference operator*() const {
            return (*it).val;
        }
        // pointer operator->() const {
        //     return &(operator* ());
        // }
        iterator(pointer p = NULL) {
            it = p;
        }
    };
    // definition for list<T>
    // construct from vector, extend another list(no copy)
    // push_back, pop_back, insert, remove, size, begin, end
    inline size_t size() const {return __length;}
    list() {
        __length = 0;
        __head = (pointer)Alloc::alloc(sizeof(node_type));
        construct(__head);
        __tail = (pointer)Alloc::alloc(sizeof(node_type));
        construct(__tail);
        __head->next = __tail;
        __tail->pre = __head;
        
    }
    list(size_t n, T val) {
        list();
        for (int i = 0; i < n; ++i)
            push_back(node_type(val));
    }
    // TODO: construct from vector<T>
    list(const vector<T>& initial_list) {
        list();
        for (int i = 0; i < initial_list.size(); ++i)
            push_back(initial_list[i]);
    }
    ~list() {
        destroy_dealloc(iterator(__head), iterator());
    }
    iterator begin() const {
        return iterator(__head->next);
    }
    iterator end() const {
        return iterator(__tail);
    }
    void insert(const size_t pos, const T& val) {
        assert(pos >=0 && pos <= __length);
        if (!(pos >=0 && pos <= __length))
            return;
        // TODO: better way for new node<T> (val), std::move?
        pointer tmp = (pointer)Alloc::alloc(sizeof(node_type));
        construct(tmp, node_type(val));
        pointer it_pos_minus1 = __locate(pos);
        pointer it_pos = it_pos_minus1->next;
        it_pos_minus1->next = tmp;
        tmp->pre = it_pos_minus1;
        tmp->next = it_pos;
        it_pos->pre = tmp;
        ++__length;
    }
    void remove(const size_t pos) {
        assert(pos >=0 && pos < __length);
        if (!(pos >=0 && pos < __length))
            return;
        pointer it_pos_minus1 = __locate(pos);
        pointer it_pos = it_pos_minus1->next;
        pointer it_pos_add1 = it_pos->next;
        destroy_dealloc(iterator(it_pos));
        it_pos_minus1->next = it_pos_add1;
        it_pos_add1->pre = it_pos_minus1;
        --__length;
    }
    void push_back(const T& val) {
        insert(__length, val);
    }
    void pop_back() {
        remove(__length-1);
    }
private:
    typedef typename iterator::node_type node_type;
    typedef typename iterator::pointer pointer;
    typedef typename iterator::reference reference;
    // head node
    pointer __head;
    // node after tail node
    pointer __tail;
    size_t __length;
    // locate to __head + pos, namely it_pos_minus1
    pointer __locate(size_t pos) const {
        pointer start;
        if (pos < __length/2) {
            start = __head;
            for (int i = 0; i < pos; i++)
                start = start->next;
        }
        else {
            start = __tail->pre;
            pos = __length-pos;
            for (int i = 0; i < pos; i++)
                start = start->pre;
        }
        return start;
    }
};
}

#endif