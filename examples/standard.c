/*
    EXAMPLE FILE
    this is for standard (non-struct) implementations,
    aka the one in easyc.h
*/
#include "../easy_api/easyc.h"

int main(){
    // you can see full list of doc in the README.md

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
    // to function properly, although it's heap memory is managed inside the function
    // so you can directly call it without having to worry for memory leak
    // prints: "true" btw
    seed(); // used if you want to randomizing string or int,
    // example:
    println(randint(0, 10)); // will randomize number between 0 to 10
    // for string:
    char* getrand = randstr(ALL, 5); // will use ALL macro string and generate string with length 5
    println(getrand);
    // don't forget to free!
    free(getrand);

    // replacing example string:
    char* getrep = repstr("You want to REPLACE game?", "REPLACE", "play");
    println(getrep);
    // free!!!
    free(getrep);
    // repstr has it's limitation it can only copy the length of TEXT (first param)
    // with only 100 bytes of memory, -1 for null termination

    // example splitting string using strsplit
    char** result; // to retrieve the substrings
    size_t len = strsplit("Split me now!", " ", &result);
    /*
    why strsplit returns size_t (size) and not direct string?
    Think of this:
    "I want to get a treasure without a map".
    That's almost impossible to determine!
    That's why strsplit returns the SIZE, which is the length that result is initialized
    for example:
    "Split me now!" will return the size of 3, which is the length of "result"
    */

    // printing the result:
    for(int i = 0; i < len; i++){
        println((char*)result[i]);
        free(result[i]);
        /*
        here we immediately frees the memory of result, as we don't need the data any longer
        keep in mind to free heap memory when it's no longer used to prevent memory leak!
        */
    }
    free(result); // freeing the result container

    // what if we want to read a single line of a file without caring it's buffer? readline will do it for you!
    int cause; // to get the cause of our errors.
    FILE* fp = fopen("anyfile.txt", "r"); // provide our file with read mode
    // don't worry, readline will check whether the file is NULL (do not exist / can't open)
    // that's why cause can become very handy!

    char* line = readline(fp, &cause); // this is a heap memory
    // although you can specify the second parameter in readline to NULL, but it's not recommended
    // if you're targetting robust app.

    printf("%s\n", line); // should print the first line
    free(line); // FREE!!!!
    /*
        what if we want to read until the end?
        we simply do:
        char* get = NULL;
        while(((get = readline(fp, &cause)) != NULL) && (cause == OPOK)){
            printf("%s\n", get);
            free(get); // since we don't use it
        }
        after that check if there's any errors
        // free(get); // absolutely safe because readline returns NULL, never a dangling pointer!
    */
    return 0;
}

// end example

/*
    END OF EXAMPLE
    That's how you use the standard functions inside easyc.h.
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
