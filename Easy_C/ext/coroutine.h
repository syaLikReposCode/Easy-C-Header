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
#include "../baseobject.h"

#define COROUTINE_BYARGS 1
#define COROUTINE_BYWRAP 2

// context switching, but in reality it's just plain case-switch

#define coroutine_context_begin(X) switch(X->yielded){
#define coroutine_context(X) case X:
#define coroutine_stop(co) \
    co->state = CoroutineSuspended\
    break;
#define coroutine_context_end(X) \
    default: break;\
    } X->state = CoroutineStopped;


// lightweight thread that performs multitasking without separating the main dispatch
struct Coroutine;

// a coroutine worker typedef.
typedef void(*cworker_t)(struct Coroutine*);

// used to determine which state is the coroutine currently
enum CoroutineState{
    CoroutineInit = 0, // indicates the task is ready to be started
    CoroutineRunning, // indicates the task is started / resumed
    CoroutineSuspended, // indicates it has been yielded or encountered coroutine_stop
    CoroutineStopped // indicates the task has finished all the context
};


typedef struct Coroutine{
    jmp_buf* context;
    enum CoroutineState state;
    cworker_t worker;
    size_t argc;
    enum ArgType* types;
    union Arg* args;
    int cotype;
    int yielded;
    void(*destroy)(struct Coroutine*); // coroutine drop model
} coroutine_t;

void coroutine_end(coroutine_t* co);

// get current coroutine state enumeration on stack-based string
const char* coroutine_get_state(enum CoroutineState state){
    switch(state){
        case CoroutineInit:
        return "ready";
        case CoroutineRunning:
        return "running";
        case CoroutineSuspended:
        return "stopped";
        case CoroutineStopped:
        return "finished";
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
    co->args = malloc(sizeof(union Arg) * argc);
    co->types = malloc(sizeof(enum ArgType) * argc);
    co->cotype = COROUTINE_BYARGS;
    co->yielded = 0;
    co->destroy = coroutine_end;
    va_list args;
    va_start(args, argc);
    for(int i = 0; i < argc; i++){
        co->types[i] = va_arg(args, enum ArgType);
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
    co->destroy = coroutine_end;
    co->context = (jmp_buf*)malloc(sizeof(jmp_buf));
    co->yielded = 0;

    return co;
}

// Starts coroutine if it's still in State::CoroutineInit state.
void coroutine_start(coroutine_t* co){
    if(co->state == CoroutineInit){
        co->state = CoroutineRunning;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// resumes the State::CoroutineSuspended coroutine.
void coroutine_resume(coroutine_t* co){
    if(co->state == CoroutineSuspended){
        co->state = CoroutineRunning;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// make the current State::CoroutineRunning coroutine State::CoroutineSuspended
void coroutine_yield(coroutine_t* co){
    if(co->state == CoroutineRunning){
        co->yielded++;
        co->state = CoroutineSuspended;
        longjmp(*(co->context), co->yielded);
    }
}

// resumes from the "TO" context.
// this functions will set :coroutine_instance:->yielded into "TO"
void coroutine_resume_static(coroutine_t* co, int to){
    if(co->state == CoroutineSuspended){
        co->yielded = to;
        co->state = CoroutineRunning;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// put new args to the coroutine, the same way you use it on coroutine_create
void coroutine_putarg(coroutine_t* co, size_t app, ...){
    if(app == 0)return;
    if(co->cotype == COROUTINE_BYWRAP){
        // checks for outside changes on types and args
        // if found, remove them
        if((co->args != NULL && co->types != NULL) && co->argc == 0){
            free(co->args);
            free(co->types);
            // preventing dangling pointer
            co->args = NULL;
            co->types = NULL;
        }
        co->args = malloc(sizeof(union Arg) * app);
        co->argc = app;
        co->types = malloc(sizeof(enum ArgType) * app);
        va_list args;
        va_start(args, app);
        for(size_t i = 0; i < app; i++){
            co->types[i] = va_arg(args, enum ArgType);
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
        return;
    }
        co->args = realloc(co->args, sizeof(union Arg) * (co->argc + app));
        co->types = realloc(co->types, sizeof(enum ArgType) * (co->argc + app));
        va_list args;
        va_start(args, app);
        for(size_t i = co->argc; i < co->argc + app; i++){
            co->types[i] = va_arg(args, enum ArgType);
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
        co->argc += app;
        va_end(args);
}

// frees the coroutine (registered in drop)
void coroutine_end(coroutine_t* co){
    free(co->args);
    free(co->types);
    free(co->context);
    free(co);
}
#endif
#endif