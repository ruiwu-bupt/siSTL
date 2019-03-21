#ifndef __SI_STACK_H
#define __SI_STACK_H

#include <assert.h>
#include <stddef.h>
#include <iostream>
#include "si_alloc.h"
#include "si_iterator.h"
#include "si_algo.h"
#include "si_traits.h"
#include "si_list.h"
#include "si_functor.h"

namespace si{
template<typename T, typename Alloc = si::simple_alloc>
class stack{
public:
    stack() {}
    stack(const si::vector<T>& initial_vector) {
        for (int i = 0; i < initial_vector.size(); i++)
            push(initial_vector[i]);
    }
    // copy constructor
    stack(const stack& that) {
        l = that.l;
    }
    stack<T>& operator=(const stack& that) {
        l = that.l;
        return *this;
    }
    void push(const T& val) {
        l.push_back(val);
    }
    void pop() {
        assert(!empty());
        l.pop_back();
    }
    T& top() {
        assert(!empty());
        return l[-1];
    }
    inline size_t size() const { return l.size();}
    inline bool empty() const { return l.size() == 0;}
private:
    si::vector<T> l;
};
}

#endif
