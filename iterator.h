#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <traits.h>
// iterator的本质是smart pointer，记住这一点
// iterator的基础模板定义
// 各种迭代器继承关系
// 暂时略去pointer_diff和size_t的萃取


struct InputIterator{};
struct OutputIterator{};
struct ForwardIterator : InputIterator{};
struct BidirectionalIterator : ForwardIterator{};
struct RandomAcessIterator : BidirectionalIterator{};

// 迭代器基类，内部使用，
template<typename T, typename IteratorCategory>
struct __Iterator_Template
{
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef IteratorCategory category;
};

// 原生指针
template<typename T, typename IteratorCategory>
struct __Iterator_Template<T*>
{
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef IteratorCategory category;
};

#endif