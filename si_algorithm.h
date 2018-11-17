#ifndef __SI_ALGORITHM_H
#define __SI_ALGORITHM_H
#include "si_iterator.h"
#include "si_traits.h"
#include "si_algo.h"

// sort for_each lower_bound upper_bound find next_permutation

namespace si{
template<typename ForwardIterator, typename functor>
void for_each(ForwardIterator begin, ForwardIterator end, functor func) {
    for (; begin != end; ++begin) {
        func(*begin);
    }
}

template<typename ForwardIterator, typename T>
ForwardIterator find(ForwardIterator begin, ForwardIterator end, const T& val) {
    for (; begin != end; ++begin) {
        if (*begin == val)
            return begin;
    }
    return end;
}

template<typename RandomAccessIterator>
void sort(RandomAccessIterator begin, RandomAccessIterator end) {
    typedef typename traits_iterator<RandomAccessIterator>::value_type T;
    si::less<T> comp;
    sort(begin, end, comp);
}

template<typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp) {
    int len = end - begin;
    if (len <= 4) {
        insert_sort(begin, end, comp);
    }
    else {
        RandomAccessIterator pivot = begin+len/2;
        partition(begin, end, pivot, comp);
        sort(begin, pivot, comp);
        sort(pivot+1, end, comp);
    }
}

template<typename RandomAccessIterator, typename Compare>
static void insert_sort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp) {
    typedef typename traits_iterator<RandomAccessIterator>::value_type T;
    int len = end - start;
    for (int i = 1; i < len; i++) {
        T tmp = *(begin+i);
        int j = i-1;
        for (; j >= 0 && comp(tmp, *(begin+j)); j--) {
            *(begin+j+1) = *(begin+j);
        }
        *(begin+j+1) = tmp;
    }
}

template<typename RandomAccessIterator, typename Compare>
static void partition(RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator pivot, Compare comp) {
    si::swap(*begin, *pivot);
    typedef typename traits_iterator<RandomAccessIterator>::value_type T;
    T tmp = *begin;
    int len = end - begin;
    int left = 0, right = len-1;
    while (left < right) {
        while (left < right && comp(*pivot, *(begin+right))) {
            --right;
        }
        *(begin+left) = *(begin+right);
        while (left < right && comp(*(begin+left), *pivot)) {
            ++left;
        }
        *(begin+right) = *(begin+left);
    }
    *(begin+left) = tmp;
}

template<typename BidirectionalIterator>
bool next_permutation(BidirectionalIterator begin, BidirectionalIterator end) {
    typedef typename traits_iterator<RandomAccessIterator>::value_type T;
    si::less<T> comp;
    next_permutation(begin, end, comp);
}

template<typename BidirectionalIterator, typename Compare>
bool next_permutation(BidirectionalIterator begin, BidirectionalIterator end, Compare comp) {
    for (int )
}


}