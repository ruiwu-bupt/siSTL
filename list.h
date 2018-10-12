#ifndef __LIST_H
#define __LIST_H

#include <alloc.h>
#include <iterator.h>
#include <si_algol.h>
#include <traits.h>

template<typename T>
struct node{
	T val;
	node* pre;
	node* next;
	typedef node self;
	node(T a) : val(a), pre(NULL), next(NULL){}
};

template<typename T>
struct __list_iterator<T, BidirectionalIterator> : __Iterator_Template<T, BidirectionalIterator>{
	typedef node<T>* iterator;
	typedef __list_iterator<T, BidirectionalIterator> self;
	iterator it;
	self& operator++() {
		it = it->next;
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++it;
		return tmp;
	}
	self& operator--() {
		it = it->pre;
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		--it;
		return tmp;
	}
	bool operator==(const self& that) const {
		return it == that.it;
	}
	bool operator!=(const self& that) const {
		return it != that.it;
	}
	reference operator*() const {
		return it->val;
	}
	iterator operator->() const {
		return it;
	}
};

template<typename T, typename Alloc = simple_alloc>
class list{
public:
	typedef __list_iterator<T> iterator;
	
private:
	// head node
	iterator __begin;
	// node after tail node
	iterator __end;
	// tail node 
	iterator __rend;
	// node before head node
	iterator __rbegin;

}