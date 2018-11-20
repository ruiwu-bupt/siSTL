#ifndef __SI_HASH_TABLE_H
#define __SI_HASH_TABLE_H
#include "si_iterator.h"
#include "si_alloc.h"
#include "si_functor.h"
#include "si_pair.h"

// using hash table for implementation
// definition of hash_func in si_functor.h need revise

template<typename kv>
struct hash_node {
    hash_node* pre;
    hash_node* next;
    kv data;
    hash_node() {
        pre = NULL;
        next = NULL;
    }
    hash_node(kv val) {
        pre = NULL;
        next = NULL;
        data = val;
    }
};

template<typename kv, typename extract_key, typename hash_func, typename equal_func, typename Alloc>
struct iterator : public __Iterator_Template<hash_node<kv>, BidirectionalIterator> {
    typedef hash_node<kv> node_type;
    typedef node_type* pointer;
    typedef node_type& reference;
    typedef kv value_type;
    typedef value_type* v_pointer;
    typedef value_type& v_reference;
    typedef hash_table<kv, extract_key, hash_func, equal_func, Alloc> ht;
    ht* tb;
    size_t pos;
    pointer it;
    typedef iterator self;
    // TODO: design problem, we can't access __nil in iterator struct
    // is __nil necessary for hash implementataion
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

template<typename kv, typename extract_key, typename hash_func, typename equal_func, typename Alloc>
class hash_table{
public:
    // constructor, copy constsructor, overload operator assignment
    // overload operator[]
    // insert, delete
    // begin, end, size, clear
    // private: bucket_num, rehash
    typedef typename iterator::node_type node_type;
    typedef typename iterator::reference reference;
    typedef typename iterator::pointer pointer;
    typedef typename iterator::value_type value_type;
    typedef typename iterator::v_reference v_reference;
    typedef typename iterator::v_pointer v_pointer;
    hash_table() {
        __head = (pointer)Alloc::alloc(sizeof(node_type));
        construct(__head);
        __begin = NULL;
        __root = NULL;
        __length = 0;
    }
    ~hash_table() {
        __destroy(__root);
    }
    inline size_t size() const { return __length;}
    inline iterator begin() const { return iterator(__begin);}
    inline iterator end() const { return iterator();}
    iterator find(const Key& k) const {
        return iterator(__find(k, false).first);
    }
    // rvalue access, read hash_table[key]
    Value operator[](const Key& k) const {       
        iterator cur = find(k);
        assert(cur.it);
        return (*cur).second;
    }
    // lvalue access, modify hash_table[key] = value
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
        
    }  
private:
    size_t __length;
    typedef hash_node<kv> node_type;
    // definition for bucket
    si::vector<node_type*> bkt;
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
