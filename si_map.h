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
    rbtree_node(Key k) {
        l = NULL;
        r = l;
        p = l;
        data = pair<Key, Value> (k);
    }
};

// 
template<typename Key, typename Value, typename Compare = less<Key>, typename Alloc = simple_alloc>
class map{
public:
    // definition for map iterator
    struct iterator : public __Iterator_Template<rbtree_node<Key, Value>, BidirectionalIterator> {
        // TODO: iterator points to pair, but it need to point to node for implementation
        // design problem, luckily they have same address since pair is the first member of node struct
        typedef rbtree_node<Key, Value> node_type;
        typedef node_type* pointer;
        typedef node_type& reference;
        typedef pair<Key, Value> value_type;
        typedef value_type* v_pointer;
        typedef value_type& v_reference;
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
                return (pointer)p;
            }
            else {
                if (p == __root)
                    return NULL;
                else if (p == p->p->r)
                    return (pointer)(p->p);
                else {
                    while (p == p->p->l)
                        p = p->p;
                    return (pointer)(p->p);
                }
            }
        }
        pointer successor(pointer p) {
            assert(p);
            if (p->r) {
                p = p->r;
                while (p->l)
                    p = p->l;
                return (pointer)p;
            }
            else {
                if (p == __root)
                    return NULL;
                else if (p == p->p->l)
                    return (pointer)(p->p);
                else {
                    while (p == p->p->r)
                        p = p->p;
                    return (pointer)(p->p);
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
        v_reference operator*() {return *(v_pointer)it;}
        v_pointer operator->() {return &(operator* ());}
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
    typedef typename iterator::node_type node_type;
    typedef typename iterator::reference reference;
    typedef typename iterator::pointer pointer;
    typedef typename iterator::value_type value_type;
    typedef typename iterator::v_reference v_reference;
    typedef typename iterator::v_pointer v_pointer;
    map() {
        __head = (pointer)Alloc::alloc(sizeof(node_type));
        __begin = NULL;
        __root = NULL;
        __length = 0;
    }
    ~map() {
        __destroy(__root);
    }
    inline size_t size() const { return __length;}
    inline iterator begin() const { return iterator(__begin);}
    inline iterator end() const { return iterator();}
    iterator find(const Key& k) const {
        return iterator(__find(k, false).first);
    }
    // rvalue access, read map[key]
    Value operator[](const Key& k) const {       
        iterator cur = find(k);
        assert(cur.it);
        return (*cur).second;
    }
    // lvalue access, modify map[key] = value
    Value& operator[](const Key& k) {
        pair<pointer, bool> tmp = __find(k, true);
        if (tmp.second) {
            pointer p2fixup = tmp.first;
            if (!__length) {
                __begin = p2fixup;
                (__head)->l = p2fixup;
                p2fixup->p = (__head);
                p2fixup->color = black;
            }
            else {
                insert_fixup(p2fixup);
            }
            ++__length;
        }
        return iterator(tmp.first)->second;
    }
    void remove(const Key& k) {
        pointer z = __find(k, false).first;
        // k don't exist
        if (!z)
            return;
        pointer y = z;
        pointer x;
        Color y_original_color = y.color;
        if (!z->l) {
            x = z->r;
            transplant(x, z);
        }
        else if (!z->r) {
            x = z->l;
            transplant(x, z);
        }
        else {
            y = tree_min(z->r);
            x = y->r;
            if (y->p == z)
                x->p = y;
            else {
                transplant(y->r, y);
                y->r = z->r;
                y->r->p = y;
            }
            transplant(y, z);
            y->l = z->l;
            y->l->p = y;
            y->color = z->color;
        }
        if (y_original_color == black)
            remove_fixup(x);
    }  
private:
    // TODO: how to destruct static pointer points to dynamic memory ?
    // may not need to destruct, only one instance, no memory leak
    // when application terminates, OS tear down everything and get memory back
    // parent of root
    pointer __head;
    // TODO: is __root declared type of pointer better?
    // we can return iterator(__begin) in begin member function
    pointer __root;
    pointer __begin;
    size_t __length;
    // TODO: static member?
    Compare comp;
    // inline void valid(pointer p) { return p != NULL;}
    // TODO: deduce equal relationship from Compare
    // not so efficient
    bool equal(const Key& k1, const Key& k2) const {
        return (comp(k1, k2) && comp(k2, k1)) ||
            (!comp(k1, k2) && !comp(k2, k1));
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
        if (pivot_p == __head)
            __root = pivot_r;
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
        if (pivot_p == __head)
            __root = pivot_l;
    }
    void transplant(pointer src, pointer dst) {
        // need do nothing case
        if (!dst)
            return;
        // corner case
        pointer dst_p = dst->p;
        if (src) {
            pointer src_p = src->p;
            if (src == src_p->l)
                src_p->l = NULL;
            else
                src_p->r = NULL;
            src->p = dst_p;
        }
        if (dst == dst_p->l)
            dst_p->l = src;
        else
            dst_p->r = src;
        if (dst_p == __head)
            __root = src;
    }
    pair<pointer, bool> __find(Key k, bool ins) {
        if (!__root) {
            if (ins) {
                __root = (pointer)Alloc::alloc(sizeof(node_type));
                construct(__root);
                __head->l = __root;
                __root->p = __head;
                __root->data.first = k;
                return pair<pointer, bool> (__root, true);
            }
            else {
                return pair<pointer, bool> (NULL, false);
            }

        }
        pointer cur = __root;
        pointer cur_p = cur->p;
        while (cur) {
            if (equal(k, cur->data.first))
                return pair<pointer, bool> (cur, false);
            else if (comp(k, cur->data.first)) {
                cur_p = cur;
                cur = cur->l;            
            }
            else {
                cur_p = cur;
                cur = cur->r;
            }
        }
        if (ins) {
            cur = (pointer)Alloc::alloc(sizeof(node_type));
            construct(cur);
            cur->data.first = k;
            if (comp(k, cur->data.first)) {            
                cur_p->l = cur;
                cur->p = cur_p;
                if (cur == __begin)
                    __begin = cur;
            }
            else {
                cur_p->r = cur;
                cur->p = cur_p;
            }
            return pair<pointer, bool> (cur, true);
        }
        else {
            return pair<pointer, bool> (NULL, false);
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
                else {
                    if (z == z->p->r) { //case 2
                        z = z->p;
                        left_rotate(z);
                    }
                    z->p->color = black; // case 3
                    z->p->p->color = red;
                    right_rotate(z->p->p);
                }
            }
            else {
                pointer y = z->p->p->l;
                if (y && y->color == red) { // case 1
                     z->p->color = black;
                     y->color = black;
                     z->p->p->color = red;
                     z = z->p->p;
                }
                else {
                    if (z == z->p->l) { //case 2
                        z = z->p;
                        right_rotate(z);
                    }
                    z->p->color = black; // case 3
                    z->p->p->color = red;
                    left_rotate(z->p->p);
                }              
            }
        }
        __root->color = black;
    }
    pointer remove_fixup(pointer x) {
        while (x != __root && x->color == black) {
            pointer w;
            if (x == x->p->l) {
                w = x->p->r;
                if (w->color == red) {  // case1
                    w->color = black;
                    x->p->color = red;
                    left_rotate(x->p);
                    w = x->p->r;
                }
                if ((!w->l || w->l->color == black) && (!w->r || w->r->color == black)) { // case2
                    w->color = red;
                    x = x->p;
                }
                else { 
                    if (w->r->color == black) { // case3
                        w->l->color = black;
                        w->color = red;
                        right_rotate(w);
                        w = x->p->r;
                    }
                    w->color = x->p->color;     // case4
                    x->p->color = black;
                    w->r->color = black;
                    left_rotate(x->p);
                    x = __root;
                }
            }
            else {
                w = x->p->l;
                if (w->color == red) {  // case1
                    w->color = black;
                    x->p->color = red;
                    right_rotate(x->p);
                    w = x->p->l;
                }
                if ((!w->l || w->l->color == black) && (!w->r || w->r->color == black)) { // case2
                    w->color = red;
                    x = x->p;
                }
                else { 
                    if (w->l->color == black) { // case3
                        w->r->color = black;
                        w->color = red;
                        left_rotate(w);
                        w = x->p->l;
                    }
                    w->color = x->p->color;     // case4
                    x->p->color = black;
                    w->l->color = black;
                    right_rotate(x->p);
                    x = __root;
                }
            }
        }
        x->color = black;
    }
    pointer tree_min(pointer r) {
        while (r && r->l)
            r = r->l;
        return r;
    }
    pointer tree_max(pointer r) {
        while (r && r->r)
            r = r->r;
        return r;
    }
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
