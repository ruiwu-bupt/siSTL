#ifndef __ALLOC_H_
#define __ALLOC_H_


// 简单的一级malloc/free配置器

#include <cstdlib>
#include <cstddef>

namespace si{
class simple_alloc
{
public:
    static void* alloc(size_t num);
    static void dealloc(void* Tp);
};

void* simple_alloc::alloc(size_t num) {
    return malloc(num);
}

void simple_alloc::dealloc(void* Tp) {
    free(Tp);
}
}

#endif