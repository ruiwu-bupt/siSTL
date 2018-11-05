#ifndef __SI_MAP_H
#define __SI_MAP_H
#include "si_iterator.h"
#include "si_alloc.h"
#include "si_functor.h"

// using red black tree for implementation
// map equals to rbtree, typedef map rbtree

enum Color {black, red};

template<typename T>
struct rbtree_node {
    T val;
    rbtree_node* l;
    rbtree_node* r;
    rbtree_node* p;
    Color color;
    rbtree_node() {
        l = NULL;
        r = l;
        p = l;
        color = black;
    }
}

// 
template<typename T, typename Compare = less<T>, typename Alloc = simple_alloc>
class map{
public:
    // definition for map iterator
    struct iterator : public __Iterator_Tempalte<rbtree_node<T>, BidirectionalIterator>{
        typedef typename __Iterator_Template<rbtree_node<T>, RandomAccessIterator>::value_type value_type;
        typedef typename __Iterator_Template<rbtree_node<T>, RandomAccessIterator>::pointer pointer;
        typedef typename __Iterator_Template<rbtree_node<T>, RandomAccessIterator>::reference reference;
        typedef typename __Iterator_Template<rbtree_node<T>, RandomAccessIterator>::category category;
        pointer it;
        pointer predecessor(pointer p) {
            assert(p && p != _nil);
            if (p->l != _nil) {
                p = p->l;
                while (p->r != _nil)
                    p = p->r;
                return p;
            }
            else {
                if (p == &*__root)
                    return _nil;
                else if (p == p->p->r)
                    return p->p;
                else {
                    while (p == p->p->l)
                        p = p->p;
                    return p->p;
                }
            }
        }
        pointer successor(pointer p) {
            assert(p && p != _nil);
            if (p->r != _nil) {
                p = p->r;
                while (p->l != _nil)
                    p = p->l;
                return p;
            }
            else {
                if (p == &*__root)
                    return _nil;
                else if (p == p->p->l)
                    return p->p;
                else {
                    while (p == p->p->r)
                        p = p->p;
                    return p->p;
                }
            }
        }
        self& operator++() {
            assert(it);
            it = it->next;
            return *th is;
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
    // constructor, copy constsructor, overload operator assignment
    // overload operator[]
    // insert, delete
    // begin, end, size, clear
    // private: predecessor, successor
    // private: left_rotate, right_rotate, transplant
    map() {
        __nil = iterator(Alloc::alloc(sizeof(value_type)));
        _nil = &*__nil;
        __root = __nil;
        __begin = __nil;
        __end = __nil;
        __length = 0;
    }
    ~map() {
        destroy_dealloc(__begin, __end);
        destroy_dealloc(__end);
    }
    inline size_t size() const { return __length;}
    inline iterator begin() const { return __begin;}
    inline iterator end() const { return __end;}

private:
    // TODO: how to destruct static pointer points to dynamic memory ?
    // may not need to destruct, only one instance, no memory leak
    // when application terminates, OS tear down everything and get memory back
    typedef iterator::pointer pointer;
    static iterator __nil;
    static pointer _nil;
    iterator __root;
    iterator __begin;
    iterator __end;
    size_t __length;
    // inline void valid(pointer p) { return p != _nil;}
    void left_rotate(pointer pivot) {
        if (!pivot || pivot == _nil)
            return;
        pointer pivot_p = pivot->p;
        pointer pivot_r = pivot->r;
        assert(pivot->r != _nil);
        pivot_r->p = pivot_p;
        if (pivot == pivot->p->l)
            pivot_p->l = pivot_r;
        else
            pivot_p->r = pivot_r;
        pivot->p = pivot_r;
        pivot->r = pivot_r->l;
        pivot_r->l->p = pivot;
        pivot_r->l = pivot;
        if (pivot_p == _nil)
            __root = iterator(pivot_r);
    }
    void right_rotate(pointer pivot) {
        if (!pivot || pivot == _nil)
            return;
        pointer pivot_p = pivot->p;
        pointer pivot_l = pivot->l;
        assert(pivot->l != _nil);
        pivot_l->p = pivot_p;
        if (pivot == pivot->p->l)
            pivot_p->l = pivot_l;
        else
            pivot_p->r = pivot_l;
        pivot->p = pivot_l;
        pivot->l = pivot_l->r;
        pivot_l->r->p = pivot;
        pivot_l->r = pivot;
        if (pivot_p == _nil)
            __root = iterator(pivot_l);
    }
    // dst is expected to be special
    // transplant function is related with delete
    // we can only delete one node once a time
    void transplant(pointer src, pointer dst) {
        if (!src || src == _nil)
            return;
        assert(dst->l == _nil && dst->r == _nil);
        pointer dst_p = dst->p;
        pointer src_p = src->p;
        if (src == src_p->l)
            src_p->l = _nil;
        else
            src_p->r = _nil;
        src->p = dst_p;
        if (dst == dst_p->l)
            dst_p->l = src;
        else
            dst_p->r = src;
        if (dst_p == _nil)
            __root = iterator(src);
    }
}
