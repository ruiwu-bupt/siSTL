#ifndef __SI_FUNCTOR_H
#define __SI_FUNCTOR_H

template<typename T>
struct less{
    bool operator()(const T& lval, const T& rval) const {
        return lval < rval;
    }
};

template<typename T>
struct greater{
    bool operator()(const T& lval, const T& rval) const {
        return lval > rval;
    }
};

template<typename T>
struct equal{
    bool operator()(const T& lval, const T& rval) const {
        return lval == rval;
    }
};

#endif