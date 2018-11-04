#ifndef __SI_MAP_H
#define __SI_MAP_H
#include "si_iterator.h"
#include "si_alloc.h"
#include "si_functor.h"

// using red black tree for implementation
template<typename T>
struct rbtree_node {
    T val;
    rbtree_node* l;
    rbtree_node* r;
    rbtree_node* p;
    int color;
    rbtree_node() {
        l = NULL;
        r = l;
        p = l;
        color = 0;
    }
}

template<typename T, typename Compare = less<T>, typename Alloc = simple_alloc>
class rb_tree{
public:
    // definition for rbtree iterator
    struct iterator : public __Iterator_Tempalte<rbtree_node<T>, BidirectionalIterator>{
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
        bool operator==(const self& that) const {return it == that.it;}
        bool operator!=(const self& that) const {return it != that.it;}
        reference operator*() const {return (*it).val;}
        pointer operator->() const {return &(operator* ());}
        iterator(pointer = NULL) {
            it = pointer;
        }
    }
    rb_tree() {
        Alloc allocer;
    }
private:
    static iterator __nil;
    iterator __begin;
    iterator __end;
}
