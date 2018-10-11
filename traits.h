#ifndef __TRAITS_H
#define __TRAITS_H

// 类型萃取器
// 判断值类型
// 函数是否有non-trivial constructer
// 判断iterator类型
template<typename T>
struct traits_type {
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
};


#endif