#ifndef __SI_PAIR_H
#define __SI_PAIR_H

#include "si_algo.h"

template<typename T1, typename T2, typename Alloc = simple_alloc>
struct pair{
	T1 first;
	T2 second;
	pair() {
		T1* p1 = Alloc.alloc((T1*)sizeof(T1));
		T2* p2 = Alloc.alloc((T2*)sizeof(T2));
		new (p1) T1(); 
		new (p2) T2();
	}
	pair(const T1& a, const T2& b) {
		T1* p1 = Alloc.alloc((T1*)sizeof(T1));
		T2* p2 = Alloc.alloc((T2*)sizeof(T2));
		new (p1) T1(a); 
		new (p2) T2(b);
	}
}

#endif