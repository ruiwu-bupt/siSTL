#ifndef __SI_FUNCTOR_H
#define __SI_FUNCTOR_H

template<typename T>
class less{
    bool operator()(const T& lval, const T& rval) const {
        return lval < rval;
    }
}

template<typename T>
class greater{
    bool operator()(const T& lval, const T& rval) const {
        return lval > rval;
    }
}

template<typename T>
class equal{
    bool operator()(const T& lval, const T& rval) const {
        return lval == rval;
    }
}
