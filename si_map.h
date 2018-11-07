#ifndef __SI_MAP_H
#define __SI_MAP_H
#include "si_iterator.h"
#include "si_alloc.h"
#include "si_functor.h"
#include "si_pair.h"

// using red black tree for implementation
// map equals to rbtree, typedef map rbtree
// TODO: no nil node leads to trivial bound case check

namespace si{
enum Color {black, red};

template<typename Key, typename Value>
struct rbtree_node {
    pair<Key, Value> data;
    rbtree_node* l;
    rbtree_node* r;
    rbtree_node* p;
    Color color;
    rbtree_node() {
        l = NULL;
        r = l;
        p = l;
        color = red;
    }
};

// 
template<typename Key, typename Value, typename Compare = less<Key>, typename Alloc = simple_alloc>
class map{
public:
    // definition for map iterator
    struct iterator : public __Iterator_Template<rbtree_node<Key, Value>, BidirectionalIterator> {
        typedef rbtree_node<Key, Value> value_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef typename __Iterator_Template<rbtree_node<Key, Value>, BidirectionalIterator>::category category;
        pointer it;
        typedef iterator self;
        // TODO: design problem, we can't access __nil in iterator struct
        // is __nil necessary for rbtree implementataion
        pointer predecessor(pointer p) {
            assert(p);
            if (p->l) {
                p = p->l;
                while (p->r)
                    p = p->r;
                return p;
            }
            else {
                if (p == &*__root)
                    return NULL;
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
            assert(p);
            if (p->r) {
                p = p->r;
                while (p->l)
                    p = p->l;
                return p;
            }
            else {
                if (p == &*__root)
                    return NULL;
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
            it = successor(it);
            return *this;
        }
        self operator++(int) {
            self tmp = *this;
            ++it;
            return tmp;
        }
        self& operator--() {
            assert(it);
            it = predecessor(it);
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
        pair<Key, Value>& operator*() {return it->data;}
        pointer operator->() {return &(operator* ());}
        iterator(pointer p=NULL) {
            it = p;
        }
    };
    // constructor, copy constsructor, overload operator assignment
    // overload operator[]
    // insert, delete
    // begin, end, size, clear
    // private: predecessor, successor
    // private: left_rotate, right_rotate, transplant
    typedef typename iterator::value_type value_type;
    typedef typename iterator::reference reference;
    typedef typename iterator::pointer pointer;
    map() {
        __head = iterator((pointer)Alloc::alloc(sizeof(value_type)));
        __length = 0;
    }
    ~map() {
        __destroy(&*__root);
    }
    inline size_t size() const { return __length;}
    inline iterator begin() const { return __begin;}
    inline iterator end() const { return __end;}
    iterator find(const Key& k) const {
        return __find(k, false).first;
    }
    // rvalue access, read map[key]
    Value operator[](const Key& k) const {       
        iterator cur = find(k);
        assert(cur != __end);
        return (*cur).second;
    }
    // lvalue access, modify map[key] = value
    Value& operator[](const Key& k) {
        pair<iterator, bool> tmp = __find(k, true);
        if (tmp.second) {
            pointer p2fixup = &*tmp.first;
            if (!__length) {
                (&*__head)->l = p2fixup;
                p2fixup->p = (&*__head);
                p2fixup->color = black;
            }
            else {
                insert_fixup(p2fixup);
            }
            ++__length;
        }
        return (*tmp.first).second;
    }
    void remove(const Key& k) {

    }  
private:
    // TODO: how to destruct static pointer points to dynamic memory ?
    // may not need to destruct, only one instance, no memory leak
    // when application terminates, OS tear down everything and get memory back
    // parent of root
    iterator __head;
    // TODO: is __root declared type of pointer better?
    // we can return iterator(__begin) in begin member function
    iterator __root;
    iterator __begin;
    iterator __end;
    size_t __length;
    // inline void valid(pointer p) { return p != NULL;}
    // TODO: deduce equal relationship from Compare
    // not so efficient
    bool equal(const Key& k1, const Key& k2) const {
        return (Compare(k1, k2) && Compare(k1, k2)) ||
            (!Compare(k1, k2) && !Compare(k1, k2));
    }
    void left_rotate(pointer pivot) {
        if (!pivot)
            return;
        pointer pivot_p = pivot->p;
        pointer pivot_r = pivot->r;
        assert(pivot_r);
        pivot_r->p = pivot_p;
        if (pivot == pivot->p->l)
            pivot_p->l = pivot_r;
        else
            pivot_p->r = pivot_r;
        pivot->p = pivot_r;
        pivot->r = pivot_r->l;
        if (pivot_r->l)
            pivot_r->l->p = pivot;
        pivot_r->l = pivot;
        if (pivot_p == &*__head)
            __root = iterator(pivot_r);
    }
    void right_rotate(pointer pivot) {
        if (!pivot)
            return;
        pointer pivot_p = pivot->p;
        pointer pivot_l = pivot->l;
        assert(pivot->l);
        pivot_l->p = pivot_p;
        if (pivot == pivot->p->l)
            pivot_p->l = pivot_l;
        else
            pivot_p->r = pivot_l;
        pivot->p = pivot_l;
        pivot->l = pivot_l->r;
        if (pivot_l->r)
            pivot_l->r->p = pivot;
        pivot_l->r = pivot;
        if (pivot_p == &*__head)
            __root = iterator(pivot_l);
    }
    // dst is expected to be special
    // transplant function is related with delete
    // we can only delete one node once a time
    void transplant(pointer src, pointer dst) {
        if (!src || !dst)
            return;
        assert(!dst->l && !dst->r);
        pointer dst_p = dst->p;
        pointer src_p = src->p;
        if (src == src_p->l)
            src_p->l = NULL;
        else
            src_p->r = NULL;
        src->p = dst_p;
        if (dst == dst_p->l)
            dst_p->l = src;
        else
            dst_p->r = src;
        if (dst_p == &*__head)
            __root = iterator(src);
    }
    // TODO: is iterator and pointer mixture usage in class appropriate?
    pair<iterator, bool> __find(Key k, bool ins) {
        pointer cur = &*__root;
        pointer cur_p = cur->p;
        while (cur) {
            if (equal(k, cur->data.first))
                return pair<iterator, bool> (iterator(cur), false);
            else if (Compare(k, cur->data.first)) {
                cur = cur->l;
                cur_p = cur;
            }
            else {
                cur = cur->r;
                cur_p = cur;
            }
        }
        if (ins) {
            cur = (pointer)Alloc::alloc(sizeof(value_type));
            new (cur) value_type();
            if (Compare(k, cur->data.first)) {            
                cur_p->l = cur;
                cur->p = cur_p;
                if (cur == &*__begin)
                    __begin = iterator(cur);
            }
            else {
                cur_p->r = cur;
                cur->p = cur_p;
            }
            return pair<iterator, bool> (iterator(cur), true);
        }
        else {
            return pair<iterator, bool> (__end, false);
        }
    }
    void insert_fixup(pointer z) {
        while (z->p->color == red) {
            if (z->p == z->p->p->l) {
                pointer y = z->p->p->r;
                if (y && y->color == red) { // case 1
                     z->p->color = black;
                     y->color = black;
                     z->p->p->color = red;
                     z = z->p->p;
                }
                else if (z == z->p->r) { //case 2
                    z = z->p;
                    left_rotate(z);
                }
                else {

                }
                z->p->color = black; // case 3
                z->p->p->color = red;
                right_rotate(z->p->p);
            }
            else {
                pointer y = z->p->p->l;
                if (y && y->color == red) { // case 1
                     z->p->color = black;
                     y->color = black;
                     z->p->p->color = red;
                     z = z->p->p;
                }
                else if (z == z->p->l) { //case 2
                    z = z->p;
                    right_rotate(z);
                }
                else {

                }
                z->p->color = black; // case 3
                z->p->p->color = red;
                left_rotate(z->p->p);
            }
        }
        (&*__root).color = black;
    }
    // inline Color& clor(pointer z) {
    //     return z ? z.color : black;
    // }
    // post order traverse for destructor
    void __destroy(pointer p) {
        if (!p)
            return;
        if (p->l)
            __destroy(p->l);
        if (p->r)
            __destroy(p->r);
        destroy_dealloc(iterator(p));
    }
};
}

#endif
