#ifndef __ALLOC_H_
#define __ALLOC_H_


// 简单的一级malloc/free配置器

#include <cstdlib>
#include <cstddef>

class simple_alloc
{
public:
    void* alloc(size_t num);
    void dealloc(void* Tp);
};

void* simple_alloc::alloc(size_t num) {
    return malloc(num);
}

void simple_alloc::dealloc(void* Tp) {
    free(Tp);
}

#endif