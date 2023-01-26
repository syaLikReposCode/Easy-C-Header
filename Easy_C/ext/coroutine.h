/*
WARNING!
This Header was completely untested on other platforms than linux, if the code does not work,
then I have to use the default OS context switching,
I only have Linux and Windows and only AMD CPU so I cannot test something on like
ARM, SPARC, Intel etc.
And I can't test something like XNU (MacOS), only NT (Windows) and Linux.
And I also have to go against Standard C (ANSI C) coding.
*/

#ifdef STRUCTS
#ifndef _EXT_COROUTINES
#define _EXT_COROUTINES 1
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

#define COROUTINE_BYARGS 1
#define COROUTINE_BYWRAP 2

// context switching, but in reality it's just plain case-switch
#define coroutine_context_begin(X) switch(X->yielded){
#define coroutine_context(X) case X:
#define coroutine_stop break;
#define coroutine_context_end \
    default: break;\
    }


// lightweight thread that performs multitasking without separating the main dispatch
struct Coroutine;

// a coroutine worker typedef.
typedef void(*cworker_t)(struct Coroutine*);

// used to determine which state is the coroutine currently
enum CoroutineState{
    CoroutineInit = 0,
    CoroutineStart,
    CoroutineSuspend
} CoState;

// argument type used to pass in the coroutine worker
typedef enum arg_t{
    INT,
    STRING,
    CHAR,
    DOUBLE,
    UINT,
    MEMORY // not type-safe, use it with care
} ArgType;

// subset of ArgType
typedef union{
    long long int_val;
    char* string;
    int char_val;
    double double_val;
    uint64_t uint_val;
    void* memory; // not type-safe, use it with care
} Arg;

typedef struct Coroutine{
    jmp_buf* context;
    enum CoroutineState state;
    cworker_t worker;
    size_t argc;
    ArgType* types;
    Arg* args;
    int cotype;
    uint64_t yielded;
} coroutine_t;

// used on debugging, get current coroutine state
const char* get_coroutine_state(enum CoroutineState state){
    switch(state){
        case CoroutineInit:
        return "Init";
        case CoroutineStart:
        return "Start";
        case CoroutineSuspend:
        return "Suspend";
        default:
        return "Unknown";
    }
}

// returns the typeof ArgType passed in the arguments
const char* arg_typeof(ArgType type){
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

// creates coroutine with arg count (argc) passed for coroutine worker
coroutine_t* coroutine_create(cworker_t worker, size_t argc, ...){
    coroutine_t* co = (coroutine_t*)malloc(sizeof(coroutine_t));
    co->state = CoroutineInit;
    co->worker = worker;
    co->argc = argc;
    co->context = (jmp_buf*)malloc(sizeof(jmp_buf));
    co->args = malloc(sizeof(Arg) * argc);
    co->types = malloc(sizeof(ArgType) * argc);
    co->cotype = COROUTINE_BYARGS;
    co->yielded = 0;
    va_list args;
    va_start(args, argc);
    for(int i = 0; i < argc; i++){
        co->types[i] = va_arg(args, ArgType);
        switch(co->types[i]){
            case INT:
                co->args[i].int_val = va_arg(args, long long);
                break;
            case STRING:
                co->args[i].string = va_arg(args, char*);
                break;
            case CHAR:
                co->args[i].char_val = va_arg(args, int);
                break;
            case DOUBLE:
                co->args[i].double_val = va_arg(args, double);
                break;
            case UINT:
                co->args[i].uint_val = va_arg(args, uint64_t);
                break;
            case MEMORY:
                co->args[i].memory = va_arg(args, void*);
                break;
            default:
                break;
        }
    }
    va_end(args);
    return co;
}

// creates a coroutine worker without passing arg count (argc)
coroutine_t* coroutine_wrap(cworker_t worker){
    coroutine_t* co = malloc(sizeof(coroutine_t));
    co->state = CoroutineInit;
    co->cotype = COROUTINE_BYWRAP;
    co->worker = worker;
    co->argc = 0;
    co->args = NULL;
    co->types = NULL;
    co->context = (jmp_buf*)malloc(sizeof(jmp_buf));
    co->yielded = 0;

    return co;
}

// Starts coroutine if it's still in State::CoroutineInit state.
void coroutine_start(coroutine_t* co){
    if(co->state == CoroutineInit){
        co->state = CoroutineStart;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// resumes the State::CoroutineSuspend coroutine.
void coroutine_resume(coroutine_t* co){
    if(co->state == CoroutineSuspend){
        co->state = CoroutineStart;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// make the current State::CoroutineStart coroutine State::CoroutineSuspend
void coroutine_yield(coroutine_t* co){
    if(co->state == CoroutineStart){
        co->yielded++;
        co->state = CoroutineSuspend;
        longjmp(*(co->context), co->yielded);
    }
}

// frees the coroutine (registered in drop)
void coroutine_end(coroutine_t* co){
    if(co->cotype == COROUTINE_BYARGS){
        free(co->args);
        free(co->types);
    }
    free(co->context);
    free(co);
}
#endif
#endif