#ifndef __VECTOR_H
#define __VECTOR_H

#include <assert.h>
#include <stddef.h>
#include <iostream>
#include "si_alloc.h"
#include "si_iterator.h"
#include "si_algo.h"
#include "si_traits.h"

namespace si{
template<typename T, typename Alloc = simple_alloc>
class vector{
public:
	struct iterator : public __Iterator_Template<T, RandomAccessIterator> {
		typedef typename __Iterator_Template<T, RandomAccessIterator>::pointer pointer;
		typedef typename __Iterator_Template<T, RandomAccessIterator>::reference reference;
		typedef typename __Iterator_Template<T, RandomAccessIterator>::category category;
		pointer it;
		typedef iterator self;
		self& operator++() {
			++it;
			return *this;
		}
		self operator++(int) {
			self tmp = *this;
			++it;
			return tmp;
		}
		self& operator--() {
			--it;
			return *this;
		}
		self operator--(int) {
			self tmp = *this;
			--it;
			return tmp;
		}
		self operator+(int step) {
			self tmp = *this;
			tmp.it += step;
			return tmp;
		}
		self operator-(int step) {
			self tmp = *this;
			tmp.it -= step;
			return tmp;
		}
		reference operator*() {
			return *it;
		}
		bool operator==(const self& that) const {
            return it == that.it;
        }
        bool operator!=(const self& that) const {
            return it != that.it;
        }
        iterator(pointer p = NULL) {
        	it = p;
        }
	};
	vector() {
		__length = 0;
		__capacity = 0;
	}
	vector(size_t n, const T& val) {
		if (!n)
			return;
		__length = n;
		__capacity = cal_capacity(n);
		__begin = iterator((T*)Alloc::alloc(__capacity * sizeof(T)));
		__end = __begin + __length;
		fill_n(__begin, __end, val);
	}
	// copy constructor
	vector(const vector& that) {
		__length = that.size();
		resize(that.size());
		__length = that.size();
		fill(that.begin(), that.end(), __begin);
	}
	vector<T> operator=(const vector& that) {
		__length = that.size();
		resize(that.size());
		__length = that.size();
		return *this;
	}
	T& operator[](int pos) {
		int n = __length;
		assert(pos >= -n && pos < n);
		return *(__begin+pos);
	}
	void push_back(const T& val) {
		insert(__length, val);
	}
	void pop_back() {
		remove(__length-1);
	}
	void insert(int pos, const T& val) {
		if (__length == __capacity)
			resize(__capacity);
		int n = __length;
		assert(pos >= -n && pos <= n);
		if (pos < 0) pos += n;
		for (iterator it = __end; it != __begin+pos; it--)
			*it = *(it-1);
		construct(&*(__begin+pos), val);
		__length++;
		++__end;
	}
	void remove(int pos) {
		int n = __length;
		assert(pos >= -n && pos < n);
		if (pos < 0) pos += n;
		destroy(&*(__begin+pos));
		for (iterator it = __begin+pos; it != __end-1; it++)
			*it = *(it+1);
		__length--;
		--__end;
	}
	void resize(size_t capacity) {
		size_t new_capacity = cal_capacity(capacity);
		iterator new_begin((T*)Alloc::alloc(new_capacity * sizeof(T)));
		fill(__begin, __end, new_begin);
		destroy(__begin, __end);
		Alloc::dealloc(&*__begin);
		__begin = new_begin;
		// 这里使用了未初始化的__length, 导致段错误，debug了好久
		__end = __begin + __length;
		__capacity = new_capacity;
	}
	inline iterator begin() const { return __begin;}
	inline iterator end() const { return __end;}
	inline size_t size() const { return __length;}
	inline size_t capacity() const {return __capacity;}
	~vector() {
		destroy(__begin, __end);
		Alloc::dealloc(&*__begin);
	}
private:
	// TODO: is 1.5 better than 2 ?
	// but standard dont't allow no-integral static const member in class
	static const int growth_factor = 2;
	static const size_t reserve_slot = 4;
	iterator __begin;
	iterator __end;
	size_t __length;
	size_t __capacity;
	size_t cal_capacity(size_t n) {
		return n*growth_factor > n+reserve_slot ? n*growth_factor : n+reserve_slot;
	}
};
}

#endif