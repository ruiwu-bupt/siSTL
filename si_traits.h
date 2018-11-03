#ifndef __TRAITS_H
#define __TRAITS_H

#include <si_iterator.h>
// 萃取器
// 对iterator萃取指向类型的相关信息
// 对普通类及原生类型判断其有无non-trivial constructer等函数


template<typename Iterator>
struct traits_iterator {
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::category category;
};

template<typename Iterator>
inline typename traits_iterator<Iterator>::value_type
value_type(Iterator) {
    typedef typename traits_iterator<Iterator>::value_type value_type;
    return value_type ();
}

template<typename Iterator>
inline typename traits_iterator<Iterator>::pointer
pointer_type(Iterator) {
    typedef typename traits_iterator<Iterator>::pointer pointer_type;
    return value_type ();
}

template<typename Iterator>
inline typename traits_iterator<Iterator>::reference
reference_type(Iterator) {
    typedef typename traits_iterator<Iterator>::reference reference_type;
    return reference_type ();
}

template<typename Iterator>
inline typename traits_iterator<Iterator>::category
category(Iterator) {
    typedef typename traits_iterator<Iterator>::category category;
    return category ();
}


template<class T>
struct __type_traits{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_False has_trivial_constructor;
    typedef __POD_False has_trivial_copy_constructor;
    typedef __POD_False has_trivial_assignment_operator;
    typedef __POD_False has_trivial_destructor;
    typedef __POD_False is_POD_type;
};

template<class T>
struct __type_traits<T*>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<char>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<wchar_t>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<unsigned char>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<short>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<unsigned short>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<int>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<unsigned int>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<long>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<unsigned long>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<long long>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<unsigned long long>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<float>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<double>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

template<>
struct __type_traits<long double>{
    // 当编译器有能力自动特化时报错可以看懂
    typedef __POD_True this_dummy_member_must_be_first;

    typedef __POD_True has_trivial_constructor;
    typedef __POD_True has_trivial_copy_constructor;
    typedef __POD_True has_trivial_assignment_operator;
    typedef __POD_True has_trivial_destructor;
    typedef __POD_True is_POD_type;
};

#endif