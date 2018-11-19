#ifndef __SI_FUNCTOR_H
#define __SI_FUNCTOR_H

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
    bool operator()(const T& val) {
        ++val;
    }
};

template<typename T>
struct decrease{
    bool operator()(const T& val) {
        --val;
    }
};
}

#endif