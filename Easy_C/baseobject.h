/*
    baseobject header contains all the functions/structs in the header need.
    and a non-existent, applicable struct trait that will
    "automatically" be embedded into the structs of the header.
    Every structs have the chance to implement their own base destructor.
    Can directly be functional (e.g. base_delete), or embed the base trait function
    named drop_fn.
    Provides arguments instance (Arg union, ArgType enum, arg_typeof) if some structs need.
*/

#ifndef _BASE_INCLUDED
#define _BASE_INCLUDED 1
#include <stdlib.h>
#include <stdint.h>

// allocates N memory of T type, returns the heap memory.
#define alloc(T, N) (T*)malloc(N)
// allocates N array memory of T type with the size of M, returns heap memory.
#define alloc_a (T, N) (T*)calloc(N, sizeof(T))



/* (Pseudo-information) that represents base trait to be applied to every structs
#set-entity nonexistent
#accessible true
#name base
#tier root
#autoembed
*/

// native drop. Frees memory, takes void* pointer as parameter.
#define drop free

// struct-defined destructor drop, calls 'drop_fn destroy' from the struct.
// The struct must be heap-allocated so it can return "this" object.
#define drops(X) X->destroy(X)

// argument type used to pass for the struct instance
enum ArgType{
    INT, // pass a 64-bit signed integer (int64_t) to the instance
    STRING, // pass a string (char*) to the instance
    CHAR, // pass a character (int) to the instance
    DOUBLE, // pass a floated-integer (double) to the instance
    UINT, // pass an unsigned 64-bit integer (uint64_t) to the instance
    MEMORY // (not type-safe, use it with care) pass reference of an object or heap memory to the instance
};

// subset of ArgType
union Arg{
    int64_t int_val;
    char* string;
    int char_val;
    double double_val;
    uint64_t uint_val;
    void* memory; // not type-safe, use it with care
};

// returns the typeof ArgType passed in the arguments
const char* arg_typeof(enum ArgType type){
    switch(type){
        case INT:
        return "int";
        case STRING:
        return "string";
        case CHAR:
        return "char";
        case DOUBLE:
        return "float";
        case UINT:
        return "unsigned";
        case MEMORY:
        return "memory";
        default:
        return "unknown";
    }
}


/*  iterator foreach.
    rules: the object must embed iter_creator_fn and name it create_iter
    with create_iter being initialized,
    the "object" instance must be a "this" object (heap-allocated)

    fallbacks:
        Hard to debug
        you cannot change it's expression behavior (like has_next)
*/
#if defined(STRUCTS) && defined(_EASY_C_HEADER)
#define foreach(object, as) for(iterator_t as = object->create_iter(object); as.has_next(as); as.next(&as))
#endif
#endif