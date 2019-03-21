#ifndef __SI_PRIORITY_QUEUE_H
#define __SI_PRIORITY_QUEUE_H

#include <assert.h>
#include <stddef.h>
#include <iostream>
#include "si_alloc.h"
#include "si_iterator.h"
#include "si_algo.h"
#include "si_traits.h"
#include "si_vector.h"
#include "si_functor.h"

namespace si{
template<typename T, typename Compare = si::greater<T>, typename Alloc = si::simple_alloc>
class priority_queue{
public:
    priority_queue(){}
    priority_queue(const si::vector<T>& initial_vector) {
        for (int i = 0; i < initial_vector.size(); i++)
            push(initial_vector[i]);
    }
    // copy constructor
    priority_queue(const priority_queue& that) {
        v = that.v;
    }
    priority_queue<T>& operator=(const priority_queue& that) {
        v = that.v;
        return *this;
    }
    void push(const T& val) {
        v.push_back(val);
        size_t pos = size()-1;
        while (pos) {
            size_t p_pos = (pos-1)/2;
            // TODO: implement swap function in si_algo
            if (comp(v[pos], v[p_pos])) {
                swap(v[pos], v[p_pos]);
            }
            pos = p_pos;
        }
    }
    void pop() {
        assert(!empty());
        v[0] = v[-1];
        v.pop_back();
        size_t p = 0;
        while (2*p+1 < size()) {
            size_t l = 2*p+1;
            size_t r = 2*p+2;
            // greater child
            size_t g;
            if (r == size())
                g = l;
            else {
                g = comp(v[l], v[r]) ? l : r;
            }
            if (comp(v[g], v[p])) {
                swap(v[g], v[p]);
                p = g;
            }
            else
                break;
        }
    }
    // does this method access queue top as rvalue in the right way
    // const function with non-reference return value fix this
    T top() const{
        assert(!empty());
        return v[0];
    }
    inline size_t size() const { return v.size();}
    inline bool empty() const { return v.size() == 0;}
private:
    si::vector<T> v;
    Compare comp;
    void swap(T& a, T& b) {
        T tmp = b;
        b = a;
        a = tmp;
    }
};
}

#endif
