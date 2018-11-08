#ifndef __SI_PAIR_H
#define __SI_PAIR_H

#include "si_algo.h"

namespace si{
template<typename T1, typename T2, typename Alloc = simple_alloc>
struct pair{
	T1 first;
	T2 second;
	pair() {
		T1* p1 = &first;
		T2* p2 = &second;
		construct(p1);
		construct(p2);
	}
	pair(const T1& a, const T2& b) {
		// 这里无脑新申请空间，用operator new，debug了好久，真的蠢。。
		T1* p1 = &first;
		T2* p2 = &second;
		construct(p1, a); 
		construct(p2, b);
	}
};
}

#endif