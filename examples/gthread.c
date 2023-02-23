/*
    EXAMPLE FILE
    gthreads are a type of thread that uses single thread
    that can execute multitasks, something like cooperatively multitasking
    note that gthreads are context-based
    I do not implement context from different OS
    the fallbacks are it gets more verbose as you yield more
    but it works using only Standard C (except for the coding though).
    The implementations is abit messy but atleast it works lol :>

    ah, also if you want to use os-specific context gthread, you can do that
    by importing "Easy_C/ext/os.h" which uses the platform-implementation
    context ;)
*/

// Advice: Try to not make unnecessary context as
// to continue from the last state I didn't use OS-specific context
// rather just a plain switch-case

// this is an example of how to use gthreads in Easy_C implementations
// no assembly needed

// firstly, gthread is a struct, we need to define STRUCTS to access it
#define STRUCTS
#include "../easy_api/ext/greenthread.h"
#include <stdio.h> // printf

/*
    because of C compilers implementation,
    it is advised that you will need to do this before accessing the drop macro
    #include "../Easy_C/ext/greenthread.h"
    #include "../Easy_C/easyc.h"

    this because most C compilers checks the #define at the top before header include
    i.e. you can't access "drop" to end gthread if the gthread is below easyc.h
    include, it sucks D:

    Same goes for typecheck macro
*/

// worker to be run in the gthread
void worker(gthread_t* co){
    // gthread context switching
    gthread_context_begin(co)
    // specify which context is this
    gthread_context(0)
    printf("Hello from context 1\n");
    gthread_yield(co);
    gthread_context(1)
    printf("Hello from context 2\n");
    gthread_context_end(co)
    /*
    the code above is equivalent to
    switch(co->yielded){
        case 0:
        printf("Hello from context 1\n");
        gthread_yield(co);
        case 1:
        printf("Hello from context 2\n");
        default:
        co->state = gthreadStopped;   
        break; // defaults here acts like break
        // although you can call gthread_stop(gthread_instance) to stop
        // execution of a context block
        // it's not recommended as you can gthread_yield
        
    }
    */
}

// another sample worker
void worker1(gthread_t* co){
    gthread_context_begin(co)
    gthread_context(0)
    printf("Hello from gthread 2!\n");
    gthread_context(1)
    printf("Hello again from gthread 2!\n");
    gthread_context_end(co)
}

// another sample worker for gthread_putarg
void example_putarg(gthread_t* co){
    gthread_context_begin(co)
    gthread_context(0)
    printf("There should be no arguments here... %zu\n", co->argc); // should print "There should be no arguments here.. 0"
    gthread_yield(co); // break to give the gthread arguments
    gthread_context(1)
    const char* a_type = arg_typeof(co->types[0]); // retrieve argument type in the gthread instance
    // it's useful if you're unsure and wants to debug which parameters passed in the union
    printf("There's argument now!! With the type %s\n (%zu)\n", a_type, co->argc); // yay we have arguments!!
    if(a_type == "int")printf("My Type has int value of: %d\n", (int)co->args[0].int_val);
    // int val by default are int64_t, so we need to cast it
    gthread_context_end(co)
}

int main(void){
    gthread_t* d = gthread_wrap(worker);
    gthread_t* abc = gthread_wrap(worker1);
    /*
    Alternatively this works with gthread_create,
    example:
    gthread_t* co1 = gthread_create(worker, 1, INT, 3); // pass 1 argc to gthread, followed by type and value
    to access the passed variable, it's provided in the struct, argc, argtype and args
    args content can be readed in the gthread.h
    here if you're lazy

    union Arg{
        long long int_val;
        char* string;
        int char_val;
        double double_val;
        uint64_t uint_val;
        void* memory; // not type-safe, use it with care
    };
    so, in the gthread, you access it like this:
    printf("%s\n", co->args[0].string);
    
    if you're unsure which arguments is passed, you can use the
    arg_typeof function that returns the argument type in string
    */
    gthread_start(d);
    // yielded gthread will return the program control to main context
    printf("Break! now let's iterate from 1 to 5\n");
    for(int i = 1; i <= 5; i++){
        printf("%d\n", i);
    }
    // execute gthread abc first and wait till it gives the control back
    gthread_start(abc);
    // resuming from the last context from gthread d.
    gthread_resume(d);
    // alternatively, you can use gthread_resume_static
    gthread_resume_static(d, 0);
    /*
        what's the difference between gthread_resume and gthread_resume_static?
        The differences is gthread_resume_static changes co->yielded
        into the specific context.
        This allows YOU and other users to have more control on the gthread context
    */
    // if you've made your mind to add new arguments to the gthread, gthread_putarg does your job!
    // here's example
    gthread_t* co_arg = gthread_wrap(example_putarg);
    gthread_start(co_arg);

    gthread_putarg(co_arg, 1, INT, 30);
    /*
        here gthread_putarg takes 2 necessary parameters
        gthread_t (task), and argument length with non-zero length,
        the following arg-len will have:
        enum ArgType, which specifies which type will the next arguments be stored in the union
        and any type previously mentioned in the parameter

        in the example above I declared gthread_putarg
        with 1 argc (argument count), with the following INT type,
        and puts 30 into it, it's important to not mismatch the input after argtype
        as it will put the arguments in the wrong union.
    */
    gthread_resume(co_arg);

    // if you want to get the current state of gthread, gthread_get_state is here for you.
    // returns
    /*
        "ready" when state is initialized (initialized, fresh, not ran yet.)
        "running" when state is started / resumed
        (this works when invoked inside the gthread)
        "stopped" when gthread is yielded or stopped
        "finished" when the gthread encounters gthread_context_end,
        never returns "finished" if there's no context control
    */

    gthread_end(d); // stops gthread 1 and free it's resources
    gthread_end(abc); // stops gthread 2 and free it's resources
    co_arg->destroy(co_arg); // or you can call hdrop directly, it's registered! (hdrop(co_arg))

    // good programmers always frees heap memory (RAM) when it's not needed, so it can be reused later
    
    // after the gthread_end is invoked towards gthread,
    // you must initialize the gthread again
    return 0;
}
/*
    My Thoughts:
    (gthread_yield_static)
    if there is gthread_resume_static that can set co->yielded to desired number (int)
    then why there's no gthread_yield_static, that can stop execution without incrementing co->yielded?
    Well I suppose you can use break statement.
    The gthread_context is just switch undercover but I gave it a little expression
    self-described macro name, if you're not happy with it and thinking it's verbose
    you can use switch, it's the same, that means gthread_context(1) is just
    case 1, when specific case in switch takes "break",
    it ignores the other case and stops the switch statement,
    that's why if you want to gthread_yield_static,
    use break; Or expressive and sets the gthread state way: "gthread_stop(co)"

    (gthread_putarg)
    ending and re-initializing the gthread to put new args to it is a pain
    so I invented this function that can append to the gthread instance
    it uses baseobject arguments management tho :)
    It's just pain to do
    // snip
    gthread_end(co);
    co = gthread_create(worker, 1, INT, 3);

    ahh who wants that?
*/

/*
    END OF EXAMPLE
    That's how you use gthread in this header implementation.
    I hope this helps!
    Thanks for reading!
*/

/*
        MIT License

    Copyright (c) 2022 syaLikShreer

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/