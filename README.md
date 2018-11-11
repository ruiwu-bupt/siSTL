[TOC]
# siSTL
`siSTL` is a toy STL inspired by sgiSTL

## development plan
### allocator
- second level memory pool for small chunk memory alloc

### iterator
- base iterator template, with type traits

### container(main part)
- vector
- string
- list
- stack
- queue
- priority_queue
- map
- set
- unordered_map
- unordered_set

### algorithm
- general constructor and destructor
- find

### functor
- commonly used funtion like less<T>, greater<T> 

## TODO
- all source code mix in `*.h`, cosider seperate implementation in `*.impl.h`
- not much class inherit as sgiSTL, good or bad?
- use valgrind for memory use analysis
- consider reverse iterator
