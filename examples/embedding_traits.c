/*
    EXAMPLE FILE
    this example shows you how to
    - Make your struct iterator
    - Register your struct in drops macro
*/

// add the header and define structs first
#define STRUCTS
#include "../Easy_C/easyc.h"

// then create your struct, let's call it array_int
struct array_int{
    // declare the needed value
    int* value; // to hold the dynamic array
    size_t size; // it's recommended to use size_t
    iterator_t(*create_iter)(struct array_int*);
    /*
        let's split it:
        iterator_t is the return type
        (*create_iter) is the function name called "create_iter"
        you can name the create_iter to any type,
        but using create_iter will register your struct in foreach macro
        and finally (struct array_int*) is your heap-allocated struct
    */
   void(*destroy)(struct array_int*);
   /*
        this member name "destroy" will register your struct in "drops" macro,
        you can name it to anything, but destroy is the default name "drops" use.
        You cannot invoke drops when this is not named "destroy"
   */
};

// creating the iterator handler
//start

// you can name it to anything, but it's recommended to be expressive so your code is readable
int array_int_has_next(iterator_t it){
    // group is a void* pointer, so you need to cast to your struct
    return it.pos < ((struct array_int*)it.group)->size;
}

// this is where you move your iterator
void array_int_next(iterator_t* it){ // takes iterator reference
    // checks whether it still can iterate this is necessary to prevent errors
    if(it->pos > ((struct array_int*)it->group)->size)return;
    it->pos++; // increments position
    it->value = &((struct array_int*)it->group)->value[it->pos]; // actually sets new value
}

iterator_t array_int_create(struct array_int* instance){
    iterator_t it;
    it.next = array_int_next; // init next function
    it.has_next = array_int_has_next; // init has_next function
    // it's recommended to initialize next and has_next for variable-independent call
    it.pos = 0; // set position
    it.group = instance; // this is where your iterator stores the full-value
    it.value = &instance->value[0]; // starting point value
    // why must be reference? Because it.value is a void pointer
    // and to get a pointer, we either reference a value, or make a heap memory of it
    return it;
}

//end

// now that's it for the iterator implementor! Now you just need to create your struct operation
//start

// let's make an alias for your struct
typedef struct array_int arr_i_t; // _t indicates type, it's optional to add it

// initializing your struct to heap and it's content

void array_i_destroy(arr_i_t* this); // prototype so it can be included in the "destroy" member

arr_i_t* array_i_new(){
    arr_i_t* arr = malloc(sizeof(arr_i_t)); // now you just created a class!
    // in java-like language the "new" operator actually does this function!
    // so when you need to create an object (Object i = new Object())
    // it actually invokes this (probably) function!

    arr->size = 0;
    arr->value = NULL;
    arr->create_iter = array_int_create; // now, you just embed your own iterator inside your struct!
    arr->destroy = array_i_destroy;
    return arr;
}

// to insert new element for your array
void array_i_push(arr_i_t* this, int elem){
    if(this->size == 0)
        // no size detected! Creates new one
        this->value = malloc(sizeof(int));
    else
        // extending your value data
        this->value = (int*)realloc(this->value, sizeof(int) * (this->size + 1));
    this->value[this->size++] = elem;
}

int array_i_get(arr_i_t* this, size_t index){
    if(index > this->size)return -1; // you wouldn't want to get your array out-of-bounds
    return this->value[index]; // return the actual value
}

void array_i_destroy(arr_i_t* this){
    free(this->value); // it removes the "value" from heap
    free(this);  // removes the data
    // an actual destructor in Java!!
}

int main(void){
    arr_i_t* arr = array_i_new(); // let's make a class object
    // inserts elements of 30 and 60
    array_i_push(arr, 30);
    array_i_push(arr, 60);
    for(iterator_t it = arr->create_iter(arr); it.has_next(it); it.next(&it)){
        int* get_ptr = (int*)it.value;
        println(*get_ptr); // should print 30 and 60 in the console
    } // or foreach(arr, it), it's the same
    drops(arr); // free when it's no longer needed
    // or you can: array_i_destroy(arr), arr->destroy(arr), it's the same.
    return 0;
}
//end

/*
    END OF EXAMPLE
    That's how you embed the base trait function called "drops"
    and an iterator, I hope this helps!
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