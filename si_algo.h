#ifndef __SI_ALGO_H
#define __SI_ALGO_H

// 基础算法，包含全局构造函数，拷贝函数
#include <cstring>
#include <new>
#include "si_traits.h"
#include "si_iterator.h"

// 广义构造函数
template<typename T1, typename T2>
void construct(T1* pointer, const T2& value) {
    new (pointer) T2(value);
}

// 广义析构函数
template<typename T>
void destroy(T* pointer) {
    pointer->~T ();
}

// 填充函数
// TODO
template<typename ForwardIterator, typename OutputIterator>
void fill(ForwardIterator begin, ForwardIterator end, OutputIterator rst) {
    for (; begin != end; ++begin, ++rst)
        construct(&*rst, *begin);
}

template<typename ForwardIterator, typename T>
void fill_n(ForwardIterator begin, ForwardIterator end, T val) {
    for (; begin != end; ++begin)
        construct(&*begin, val);
}

template<typename ForwardIterator>
void destroy(ForwardIterator begin, ForwardIterator end) {
    typedef typename traits_iterator<ForwardIterator>::value_type value_type;
    typedef typename __type_traits<value_type>::has_trivial_destructor __POD_Type;
    destroy_aux(begin, end, __POD_Type());
}

// do nothing
template<typename ForwardIterator>
void destroy_aux(ForwardIterator begin, ForwardIterator end, __POD_True) {

}

// call destructor
template<typename ForwardIterator>
void destroy_aux(ForwardIterator begin, ForwardIterator end, __POD_False) {
    for(; begin != end; ++begin)
        destroy(&*begin);
}

#endif