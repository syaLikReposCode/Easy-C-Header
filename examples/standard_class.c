/*
    EXAMPLE FILE
    this file contains the example of using the standard (easyc.h) class in this header.
    first we need to define STRUCTS to access the class.
*/
#define STRUCTS
#include "../easy_api/easyc.h"

int main(){
    /*
        Now you've unlocked the standard classes in EasyC header!
        and you shall not use iterator_t directly as it's not a class,
        rather it's a trait,
        trait or interface is like a placeholder that any structs / classes can implement,
        their necessary functions / member must be declared when implemented / embedded.
        Example of map_t which implements the trait of iterator so it can traverse it's element
        in pair.

        Iterator is connected to foreach,
        that's for another example file called "embedding_traits.c",
        which shows you how you can embed the traits on your own structs,
        also keep in mind to learn how embedding works without inheritance,
        see behind the curtain!
    */
    // array example
    array_t* a = array_new(30);
    /*
        this creates an array with the elementSize of 30
        the array_t is not modified by me yet it still uses v1 array_t
    */
    array_push(a, "hello world!");
    /*
        array_push only takes string as it's parameter
        although it explicitly says "void*"
        but it still uses v1, so sorry for the inconvenience!

        array_push has a cousin named array_insert,
        it differs from array_push, array_insert takes 3 parameter:
        array_t* this, size_t pos, void* elem
        which inserts the element into the "pos" position, pretty neat huh?
    */
    char* get = (char*)array_get(a, 0);
    println(get); // prints: "hello world!"
    array_set(get, 0, "worldo!"); // now index 0 is no longer "hello world1"
    // the equivalent if you want to set an int inside the array is array_set_int
    array_remove(a, 0); // removes the first element of the array
    /*
        Worth noting array_t still uses v1 array, so array_remove and other functions
        may be broken.
    */
    array_print(a); // prints: ["worldo!"]

    array_destroy(a);
    // as array_t still uses v1, it does not comply on the new baseobject concept 
    // and it's not iterable yet
    // maybe soon?

    // pair is a type of key-value, it has 2 functions to create pair
    // pair_make, allocates pair in heap memory, useful for embedding in struct when the value can be changed
    // pair_create, allocates pair in stack memory, useful for quick, non-free value
    pair_t* p = pair_make("abd", "Yo I got pair!!");
    println((char*)p->value); // prints: "Yo I got pair!!"
    println((char*)p->key); // prints: "abd"
    p->destroy(p); // destroy only works in pair_make, do not try call pair_destroy on pair_create!

    // map, or can be called "a wrapper for arrays of pair" in this header impl
    map_t* mp = map_new();
    // inserts the key of abc with value of Za warudo!!
    // like array, it uses string for now, as void* is not type safe!
    // in json, it's equivalent to:
    // "abc": "Za warudo!!"
    map_insert(mp, "abc", "Za warudo!!");
    println((char*)map_get(mp, 0)); // prints Za warudo!!
    map_insert(mp, "find_me", "You found me!");
    // it is advised to put a key like you define identifier
    // no space or any weird characters, only underscore
    println((char*)map_find(mp, "find_me")); // prints "You found me!"
    // the time complexity of map_find is O(N), where N is the size of an array
    /*
        What's time complexity?
        It's a name used in programming to measure the computation time,
        it uses mathematic notation called: "Big O Notation"
        for example:
        for(int i = 0; i < 10; i++){}
        adds to N time complexity, where N is 10, so the big O notation is O(N)
        it's like the one in Sigma
        the more you add for loops, example 2 loops in one function
        the N increases,
        if you have 2 loops inside a function, then your function
        time complexity is O(2N)
        you can read more here: https://en.wikipedia.org/wiki/Time_complexity
    */
    map_set(mp, "find_me", "I'm here now!"); // sets the "find_me" to "I'm here now!"
    println((char*)map_find(mp, "find_me"));
    map_print(mp); // prints: {"abc": "Za warudo!!", "find_me": "I'm here now!"}
    // although map_print is the native function, it's wrapped in print and println
    // so you can directly call: println(mp);

    // map is iterable and registered in foreach, so you can do your operation
    // on iterating the map.

    map_delete_id(mp, 0); // deletes Za warudo!! goodbye! (for delete by key, use map_delete)
    drops(mp); // or mp->destroy(mp)
    return 0;
}

// end

/*
    END OF EXAMPLE
    That's how you use the STRUCTS members correctly.
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