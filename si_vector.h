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
		length = 0;
		capacity = 0;
	}
	vector(size_t n, T val) {
		if (!n)
			return;
		Alloc allocator;
		length = n;
		capacity = n*1.5 > n+4 ? n*1.5 : n+4;
		__begin = iterator(allocator.alloc(capacity * sizeof(T)));
		__end = __begin + length;
		fill_n(__begin, __end, val);
	}
private:
	iterator __begin;
	iterator __end;
	size_t length;
	size_t capacity;
}

#endif