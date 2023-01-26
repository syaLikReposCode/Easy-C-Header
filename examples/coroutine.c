/*
    EXAMPLE FILE
    Coroutines are a type of thread that uses single thread
    that can execute multitasks, something like cooperatively multitasking
    note that coroutines are context-based
    I do not implement context from different OS
    the fallbacks are it gets more verbose as you yield more
    but it works using only Standard C (except for the coding though).
    The implementations is abit messy but atleast it works lol :>
*/

// Advice: Try to not make unnecessary context as
// to continue from the last state I didn't use OS-specific context
// rather just a plain switch-case

// this is an example of how to use coroutines in Easy_C implementations
// no assembly needed

// firstly, coroutine is a struct, we need to define STRUCTS to access it
#define STRUCTS
#include "../Easy_C/ext/coroutine.h"

/*
    because of C compilers implementation,
    it is advised that you will need to do this before accessing the drop macro
    #include "../Easy_C/ext/coroutine.h"
    #include "../Easy_C/easyc.h"

    this because most C compilers checks the #define at the top before header include
    i.e. you can't access "drop" to end coroutine if the coroutine is below easyc.h
    include, it sucks D:

    Same goes for typecheck macro
*/

// worker to be run in the coroutine
void worker(coroutine_t* co){
    // coroutine context switching
    coroutine_context_begin(co)
    // specify which context is this
    coroutine_context(0)
    printf("Hello from context 1\n");
    coroutine_yield(co);
    coroutine_context(1)
    printf("Hello from context 2\n");
    coroutine_context_end
    /*
    the code above is equivalent to
    switch(co->yielded){
        case 0:
        printf("Hello from context 1\n");
        coroutine_yield(co);
        case 1:
        printf("Hello from context 2\n");
        default:
        break; // defaults here acts like break
        // although you can call coroutine_stop to stop
        // execution of a context block
        // it's not recommended as you can coroutine_yield
        
    }
    */
}

// another sample worker
void worker1(coroutine_t* co){
    coroutine_context_begin(co)
    coroutine_context(0)
    printf("Hello from coroutine 2!\n");
    coroutine_context(1)
    printf("Hello again from coroutine 2!\n");
    coroutine_context_end
}

int main(void){
    coroutine_t* d = coroutine_wrap(worker);
    coroutine_t* abc = coroutine_wrap(worker1);
    /*
    Alternatively this works with coroutine_create,
    example:
    coroutine_t* co1 = coroutine_create(worker, 1, INT, 3); // pass 1 argc to coroutine, followed by type and value
    to access the passed variable, it's provided in the struct, argc, argtype and args
    args content can be readed in the coroutine.h
    here if you're lazy

    union Arg{
        long long int_val;
        char* string;
        int char_val;
        double double_val;
        uint64_t uint_val;
        void* memory; // not type-safe, use it with care
    };
    so, in the coroutine, you access it like this:
    printf("%s\n", co->args[0].string);
    
    if you're unsure which arguments is passed, you can use the
    arg_typeof function that returns the argument type in string
    */
    coroutine_start(d);
    // yielded coroutine will return the program control to main context
    printf("Break! now let's iterate from 1 to 5\n");
    for(int i = 1; i <= 5; i++){
        printf("%d\n", i);
    }
    // execute coroutine abc first and wait till it gives the control back
    coroutine_start(abc);
    // resuming from the last context from coroutine d.
    coroutine_resume(d);
    coroutine_end(d); // stops coroutine 1 and free it's resources (drop in easyc.h)
    coroutine_end(abc); // stops coroutine 2 and free it's resources (drop in easyc.h)
    // good programmers always frees heap memory (RAM), so it can be reused later
    return 0;
}