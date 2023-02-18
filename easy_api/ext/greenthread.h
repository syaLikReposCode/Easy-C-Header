/*
WARNING!
This Header was completely untested on other platforms than linux, if the code does not work,
then I have to use the default OS context switching,
I only have Linux and Windows and only AMD CPU so I cannot test something on like
ARM, SPARC, Intel etc.
And I can't test something like XNU (MacOS), only NT (Windows) and Linux.
*/

#ifdef STRUCTS
#ifndef _EXT_GREEN_THREADS
#define _EXT_GREEN_THREADS 1
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../baseobject.h"

#define GTHREAD_BYARGS 1
#define GTHREAD_BYWRAP 2

// context switching, but in reality it's just plain case-switch

#define gthread_context_begin(X) switch(X->yielded){
#define gthread_context(X) case X:
#define gthread_stop(co) \
    co->state = GThreadSuspended;\
    break;
#define gthread_context_end(X) \
    default: \
    co->state = GThreadStopped; \
    break;\
    }


// lower-overhead version of threads, uses the concept of cooperative multitasking
struct GreenThread;

// a gthread worker typedef.
typedef void(*gworker_t)(struct GreenThread*);

// used to determine which state is the green thread currently
enum GThreadState{
    GThreadInit = 0, // indicates the task is ready to be started
    GThreadRunning, // indicates the task is started / resumed
    GThreadSuspended, // indicates it has been yielded or encountered gthread_stop
    GThreadStopped // indicates the task has finished all the context
};


typedef struct GreenThread{
    jmp_buf* context;
    enum GThreadState state;
    gworker_t worker;
    size_t argc;
    enum ArgType* types;
    union Arg* args;
    int cotype;
    int yielded;
    void(*destroy)(struct GreenThread*); // green thread drop model
} gthread_t;

void gthread_end(gthread_t* co);

// get current gthread state enumeration on stack-based string
const char* gthread_get_state(enum GThreadState state){
    switch(state){
        case GThreadInit:
        return "ready";
        case GThreadRunning:
        return "running";
        case GThreadSuspended:
        return "stopped";
        case GThreadStopped:
        return "finished";
        default:
        return "unknown";
    }
}

// creates gthread with arg count (argc) passed for gthread worker
gthread_t* gthread_create(gworker_t worker, size_t argc, ...){
    gthread_t* co = (gthread_t*)malloc(sizeof(gthread_t));
    co->state = GThreadInit;
    co->worker = worker;
    co->argc = argc;
    co->context = (jmp_buf*)malloc(sizeof(jmp_buf));
    co->args = malloc(sizeof(union Arg) * argc);
    co->types = malloc(sizeof(enum ArgType) * argc);
    co->cotype = GTHREAD_BYARGS;
    co->yielded = 0;
    co->destroy = gthread_end;
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

// creates a gthread worker without passing arg count (argc)
gthread_t* gthread_wrap(gworker_t worker){
    gthread_t* co = malloc(sizeof(gthread_t));
    co->state = GThreadInit;
    co->cotype = GTHREAD_BYWRAP;
    co->worker = worker;
    co->argc = 0;
    co->args = NULL;
    co->types = NULL;
    co->destroy = gthread_end;
    co->context = (jmp_buf*)malloc(sizeof(jmp_buf));
    co->yielded = 0;

    return co;
}

// Starts gthread if it's still in State::gthreadInit state.
void gthread_start(gthread_t* co){
    if(co->state == GThreadInit){
        co->state = GThreadRunning;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// resumes the State::GThreadSuspended gthread.
void gthread_resume(gthread_t* co){
    if(co->state == GThreadSuspended){
        co->state = GThreadRunning;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// make the current State::gthreadRunning gthread State::gthreadSuspended
void gthread_yield(gthread_t* co){
    if(co->state == GThreadRunning){
        co->yielded++;
        co->state = GThreadSuspended;
        longjmp(*(co->context), co->yielded);
    }
}

// resumes from the "TO" context.
// this functions will set :gthread_instance:->yielded into "TO"
void gthread_resume_static(gthread_t* co, int to){
    if(co->state == GThreadSuspended){
        co->yielded = to;
        co->state = GThreadRunning;
        if(setjmp(*(co->context)) == 0){
            co->worker(co);
        }
    }
}

// put new args to the gthread, the same way you use it on gthread_create
void gthread_putarg(gthread_t* co, size_t app, ...){
    if(app == 0)return;
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

// frees the gthread (registered in drop)
void gthread_end(gthread_t* co){
    free(co->args);
    free(co->types);
    free(co->context);
    free(co);
}
#endif
#endif
