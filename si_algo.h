#ifndef __SI_ALGO_H
#define __SI_ALGO_H

// 基础算法，包含全局构造函数，拷贝函数
#include <cstring>
#include <new>
#include "si_traits.h"
#include "si_iterator.h"

// 填充函数
// TODO
template<typename ForwardIterator, typename OutputIterator>
void fill(ForwardIterator& start, ForwardIterator& end, OutputIterator rst) {
    for (; start != end; ++start, ++rst)
        *rst = *start;
}

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

void destroy(ForwardIterator first, ForwardIterator last) {
    typedef typename value_type(first) value_type;
    typedef typename __type_traits<value_type>::has_trivial_destructor __POD_Type;
    destroy_aux(first, last, __POD_Type());
}

// do nothing
void destroy_aux(ForwardIterator first, ForwardIterator last, __POD_True) {

}

// call destructor
void destroy_aux(ForwardIterator first, ForwardIterator last, __POD_Flase) {
    for(; first != last; ++first)
        destroy(&*first);
}

#endif