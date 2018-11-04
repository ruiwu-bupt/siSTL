#ifndef __ITERATOR_H
#define __ITERATOR_H

// iterator的本质是smart pointer，记住这一点
// iterator的基础模板定义
// 各种迭代器继承关系
// 暂时略去pointer_diff和size_t的萃取

// 是否为pod类型，是否拥有trivial constructer
struct __POD_False{};
struct __POD_True{};

struct InputIterator{};
struct OutputIterator{};
struct ForwardIterator : InputIterator{};
struct BidirectionalIterator : ForwardIterator{};
struct RandomAccessIterator : BidirectionalIterator{};

// 迭代器基类，内部使用，
template<typename T, typename IteratorCategory>
struct __Iterator_Template : public ForwardIterator
{
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef IteratorCategory category;
};

// 原生指针
template<typename T, typename IteratorCategory>
struct __Iterator_Template<T*, IteratorCategory>
{
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef IteratorCategory category;
};

#endif