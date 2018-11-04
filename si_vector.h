#ifndef __VECTOR_H
#define __VECTOR_H

#include <assert.h>
#include <stddef.h>
#include <si_alloc.h>
#include <si_iterator.h>
#include <si_algo.h>
#include <si_traits.h>
#include <si_vector.h>

template<typename T, typename Alloc = simple_alloc>
class vector{
public:
	struct iterator : public __Tterator_Template<T, RandomAccessIterator> {
		typedef iterator self;
		pointer it;
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
        iterator(pointer = NULL) {
        	it = pointer;
        }
	}
	vector() {
		__length = 0;
		__capacity = 0;
	}
	vector(size_t n, T val) {
		if (!n)
			return;
		__length = n;
		__capacity = cal_capacity(n);
		__begin = iterator(Alloc.alloc(__capacity * sizeof(T)));
		__end = __begin + __length;
		fill_n(__begin, __end, val);
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
		length++;
		++__end;
	}
	void remove(int pos) {
		int n = __length;
		assert(pos >= -n && pos < n);
		if (pos < 0) pos += n;
		destroy(&*(__begin+pos));
		for (iterator it = __begin+pos; it != end-1; it++)
			*it = *(it+1);
		length--;
		--__end;
	}
	void resize(size_t capacity) {
		size_t new_capacity = cal_capacity(capacity);
		iterator new_begin((T*)Alloc.alloc(new_capacity * sizeof(T)));
		fill(__begin, __end, new_begin);
		destroy(__begin, __end);
		Alloc.dealloc(&*__begin);
		__begin = new_begin;
		__end = __begin + __length;
		__capacity = new_capacity;
	}
	iterator begin() const { return __begin;}
	interator end() const { return __end;}
	size_t size() const { return __length;}
	size_t capacity() const {return __capacity;}
	~vector() {
		destroy(__begin, __end);
		Alloc.dealloc(&*__begin);
	}
private:
	static const float growth_factor = 1.5;
	static const size_t reserve_slot = 4;
	iterator __begin;
	iterator __end;
	size_t __length;
	size_t __capacity;
	size_t cal_capacity(size_t n) {
		return n*growth_factor > n+reserve_slot ? n*growth_factor : n+reserve_slot;
	}
}

#endif