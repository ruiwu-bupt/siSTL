#ifndef __ITERATOR_H
#define __ITERATOR_H

// iterator的基础模板定义
// 各种迭代器继承关系
struct InputIterator{};
struct OutputIterator{};
struct ForwardIterator : InputIterator{};
struct BidirectionalIterator : ForwardIterator{};
struct RandomAcessIterator : BidirectionalIterator{};

// 是否为pod类型，是否拥有trivial constructer
struct __is_False{};
struct __is_True{};


#endif