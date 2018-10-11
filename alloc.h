#ifndef __ALLOC_H_
#define __ALLOC_H_

#include <cstdlib>
#include <cstddef>

template<typename T>
class alloc_template
{
public:
	void* alloc(size_t num, T inst);
	void dealloc(T* Tp);
};

template<typename T>
void* alloc_template<T>::alloc(size_t num, T inst){
	return malloc(num * sizeof(T));
}

template<typename T>
void alloc_template<T>::dealloc(T* Tp){
	free(Tp);
}

#endif