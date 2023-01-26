/*
    EXAMPLE FILE
    this is for standard (non-struct) implementations,
    aka the one in easyc.h
*/
#include "../Easy_C/easyc.h"

int main(){
    // you can see full list of doc in the README.md
    // get the current compiler kernel name
    char* ken = kernel_name(); // this is stored in heap
    println(ken); // because ken is actually a void* undercover, we need to cast to char*
    // in my case, ken will print "linux" as I am debugging this on Linux
    // but it's already wrapped by strtolower
    free(ken); // good programmer always free heap memory

    char* getlower = strtolower("ABCDEFG"); // heap memory... again! It's opposite are strtoupper
    // the lowercase uses ctype.h so I'm assuming it's ANSI string
    println(getlower); // should print "abcdefg"
    free(getlower); // always free when it's not needed!
    // becareful of double-free, as "free" will free actual memory
    // and the free again will free NULL which causes Segfault

    int d = 3;
    println(typecheck(d)); // typecheck returns direct string on stack
    // so no heap memory is involved, and it will print "integer"

    println((_Bool)strcmpcase("ABCD", "abcd")); // strcmpcase utilizes strtolower
    // to function properly, although it's heap memory is automatically managed
    // so you can directly call it without having to worry for memory leak
    // prints: "true" btw
    seed(); // used if you want to randomizing string or int,
    // example:
    println(randint(0, 10)); // will randomize number between 0 to 10
    // for string:
    char* get = randstr(ALL, 5); // will use ALL macro string and generate string with length 5
    println(get);
    // don't forget to free!
    free(get);

    // replacing example string:
    char* get = repstr("You want to REPLACE game?", "REPLACE", "play");
    println(get);
    // free!!!
    free(get);
    // repstr has it's limitation it can only copy the length of TEXT (first param)
    // with only 100 bytes of memory, -1 for null termination
    return 0;
}

// end example