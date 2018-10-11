#ifndef __SI_ALGO_H
#define __SI_ALGO_H

// 基础算法，包含全局构造函数，拷贝函数
#include <cstring>
#include <new>

// 填充函数
// TODO
template<typename InputIterator, typename OutputIterator>
void fill(InputIterator& start, InputIterator& end, OutputIterator rst) {
	for (; start != end; ++start, ++rst)
		*rst = *start;
}

// 广义构造函数
template<typename T1, typename T2>
void construct(T1* pointer, T2& value) {
	new (pointer) T2(value);
}

// 广义析构函数
template<typename T>
void destroy(T* pointer) {
	pointer->~T ();
}

#endif