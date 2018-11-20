#ifndef __SI_FUNCTOR_H
#define __SI_FUNCTOR_H

#include <stddef.h>
namespace si{
template<typename T>
struct less{
    bool operator()(const T& lval, const T& rval) const {
        return lval < rval;
    }
};

struct less_equal{
    bool operator()(const T& lval, const T& rval) const {
        return lval <= rval;
    }
};

template<typename T>
struct greater{
    bool operator()(const T& lval, const T& rval) const {
        return lval > rval;
    }
};

struct greater_equal{
    bool operator()(const T& lval, const T& rval) const {
        return lval >= rval;
    }
};

template<typename T>
struct unequal{
    bool operator()(const T& lval, const T& rval) const {
        return lval != rval;
    }
};

template<typename T>
struct equal{
    bool operator()(const T& lval, const T& rval) const {
        return lval == rval;
    }
};

template<typename T>
struct increace{
    bool operator()(const T& val) const {
        ++val;
    }
};

template<typename T>
struct decrease{
    bool operator()(const T& val) const {
        --val;
    }
};

template<typename T>
struct hash_func{
    // TODO: int, char will also be hashed
    // is this rational?
    size_t hash_object(const T& val) const {
        size_t sum = 0;
        char* s = (char*)&T;
        size_t len = sizeof(T);
        for (int i = 0; i < len; i++)
            sum = 3*sum + *s;
        return sum;
    }
};
}

#endif