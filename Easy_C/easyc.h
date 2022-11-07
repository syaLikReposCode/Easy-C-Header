// WARNING! THIS HEADER IS FOR C ONLY! DO NOT INCLUDE THIS HEADER WITH C++
// for C++ please use the .hpp version [Coming Soon]
#define __AUTHOR "syaLikShreer"
#define __EASY_C_VERSION 2
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#define ALL "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define LETTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ASCII_LOWER "abcdefghijklmnopqrstuvwxyz"
#define ASCII_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SYMBOL "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define DIGITS "0123456789"
#define typecheck(T) _Generic( (T), int: "integer", \
                              _Bool: "boolean", \
                              char*: "string",\
                              char: "character", \
                              double: "double", \
                              float: "float", \
                              long: "long",\
                              short: "short", \
                              void *: "null", \
                               default: "unknown")

// Begin Print macro

void printString(char * arg){
    printf("%s", arg);
}
void printInt(int arg){
    printf("%d", arg);
}
void printChar(char arg){
    printf("%c", arg);
}
void printBool(_Bool arg){
    printf("%s", (arg) ? "true" : "false");
}
void printNone(){
    printf("");
}
void printDouble(double arg){
    printf("%lf", arg);
}
void printLongDb(long double arg){
    printf("%Lf", arg);
}
void printFloat(float arg){
    printf("%f",arg);
}

// Uses generic template to fulfill template
#define print(X) _Generic((X), int: printInt, \
                              _Bool: printBool, \
                              char*: printString,\
                              char: printChar, \
                              double: printDouble, \
                              long double: printLongDb, \
                              float: printFloat, \
                              size_t: printInt, \
                               default: printNone)(X)
void printStringln(char * arg){
    printf("%s\n", arg);
}
void printIntln(int arg){
    printf("%d\n", arg);
}
void printCharln(char arg){
    printf("%c\n", arg);
}
void printBoolln(_Bool arg){
    printf("%s\n", (arg) ? "true" : "false");
}
void printNoneln(){
    printf("\n");
}
void printDoubleln(double arg){
    printf("%lf\n", arg);
}
void printLongDbln(long double arg){
    printf("%Lf\n", arg);
}
void printFloatln(float arg){
    printf("%f\n",arg);
}

#define println(X) _Generic((X), int: printIntln, \
                              _Bool: printBoolln, \
                              char*: printStringln,\
                              char: printCharln, \
                              double: printDoubleln, \
                              long double: printLongDbln, \
                              float: printFloatln, \
                              size_t: printIntln, \
                               default: printNoneln)(X)

// End print macro

// returns lowered string, stored in heap [heap]
char* strtolwr(char* str){
    char res[strlen(str)];
    size_t size = strlen(str);
    for(int i = 0; i < size; i++){
        char get = str[i];
        char lwred = tolower(get);
        res[i] = lwred;
    }
    res[size] = '\0';
    return strdup(res);
}
// returns upper string, stored in heap [heap]
char* strtoupper(char* str){
    char res[strlen(str)];
    size_t size = strlen(str);
    for(int i = 0; i < size; i++){
        char get = str[i];
        char lwred = toupper(get);
        res[i] = lwred;
    }
    res[size] = '\0';
    return strdup(res);
}

// replaces string if found [heap]
char * repstr(char * text, char * old, char * newstr){
    char * res = (char *)malloc(sizeof(char) * 100);
    strcpy(res, text);
    char * p = strstr(res, old);
    while(p){
        strcpy(p, newstr);
        p += strlen(newstr);
        p = strstr(p, old);
    }
    return res;
}
// generates pseudo-random number and then add to min-max (seed call is required)
int randint(int min, int max){
    if(min >= max){
        int temp = min;
        min = max;
        max = temp;
    }
    int res = rand() % (max - min + 1) + min;
    return res;
}
void seed(){srand(time(NULL));}
// generates pseudo-random string based on length specified (seed call is required) [heap]
char * randstr(char* str,int length){ 
    char * res = (char *)malloc(sizeof(char) * length);
    for(int i = 0; i<length; i++){
        res[i] = str[randint(0, strlen(str))];
        if(i == length-1){
            res[i+1] = '\0';
        }
    }
    return res;
}

// unsafe functions by default are locked because of possible NULL return and low-level management
#ifdef UNSAFE_LOCK
// start of array struct

typedef struct{
    void * data;
    int length;
    int capacity;
    int elementSize;
} array_t;
array_t * array_new(int elementSize){
    array_t * a = malloc(sizeof(array_t));
    a->data = malloc(sizeof(elementSize));
    a->length = 0;
    a->capacity = 1;
    a->elementSize = elementSize;
    return a;
}
void * array_get(array_t * a, int index){
    if(index < 0 || index >= a->length)
        return NULL;
    return (char *)a->data + index * a->elementSize;
}
void array_push(array_t * a, void * element){
    if(a->length == a->capacity){
        a->capacity *= 2;
        a->data = realloc(a->data, a->capacity * a->elementSize);
    }
    memcpy((char *)a->data + a->length * a->elementSize, element, a->elementSize);
    a->length++;
}

void array_destroy(array_t * a){
    free(a->data);
    free(a);
}

int array_get_int(array_t * a, int index){
    if(index < 0 || index >= a->length)
        return 0;
    return (int)strtol(array_get(a, index), (char **)NULL, 10);
}

void array_remove(array_t * a, int index){
    if(index < 0 || index >= a->length)
        return;
    for(int i = index; i < a->length - 1; i++){
        memcpy((char *)a->data + i * a->elementSize, (char *)a->data + (i + 1) * a->elementSize, a->elementSize);
    }
    a->length--;
}

void array_insert(array_t * a, int index, void * element){
    if(index < 0 || index >= a->length)
        return;
    if(a->length == a->capacity){
        a->capacity *= 2;
        a->data = realloc(a->data, a->capacity * a->elementSize);
    }
    for(int i = a->length; i > index; i--){
        memcpy((char *)a->data + (i + 1) * a->elementSize, (char *)a->data + i * a->elementSize, a->elementSize);
    }
    memcpy((char *)a->data + index * a->elementSize, element, a->elementSize);
    a->length++;
}

void array_print(array_t * a){
    printf("[");
    for(int i = 0; i < a->length; i++){
        if(i != 0)
            printf(", ");
         printf("%s", (char*)array_get(a, i));
    }
    printf("]");
}
void array_set(array_t * a, int index, void * element){
    if(index < 0 || index >= a->length)
        return;
    memcpy((char *)a->data + index * a->elementSize, element, a->elementSize);
}
void array_set_int(array_t * a, int index, int value){
    if(index < 0 || index >= a->length)
        return;
    char * s = malloc(sizeof(int));
    sprintf(s, "%d", value);
    array_set(a, index, s);
    free(s);
}

// end of array struct


// begin of map

// data lists for map
typedef struct{
    char* key;
    void* value;
} data_list;

// map type, utilizes heap storage for use
typedef struct{
    data_list* data;
    size_t size;
    int elemSize;
} map_t;

// initializes empty map
map_t* map_new(int elemSize){
    map_t* map;
    map = malloc(sizeof(map_t));

    map->size = 0;
    map->data = NULL;
    map->elemSize = elemSize;
    return map;
}

// insert value to map, value can only store string for now.
void map_insert(map_t* mp, char* key, void* value){
    char* nkey = (char*)malloc(strlen(key)+1);
    strcpy(nkey, key);

    if(mp->size == 0){
        mp->data = malloc(sizeof(data_list));
        mp->data->key = nkey;
        mp->data->value = value;
        mp->size++;
    }else{
        mp->data = realloc(mp->data, sizeof(data_list) * (mp->size + 1));
        (mp->data + mp->size)->key = nkey;
        (mp->data + mp->size)->value = value;
        mp->size++;
    }
}

// get map data by index (useful for iterator)
void* map_get(map_t* mp, size_t index){
    if(index > mp->size)
        return NULL;
    return (mp->data + index)->value;
}

// get map by keyname (useful if index is unknown)
void* map_find(map_t* mp, char* key){
    for(size_t i = 0; i < mp->size; i++){
        if(strcmp((mp->data + i)->key, key) == 0){
            return (mp->data + i)->value;
        }
    }
    return NULL;
}


// frees heap from map
void map_destroy(map_t* mp){
    for(size_t i = 0; i < mp->size; i++){
        free((mp->data + i)->value);
        free((mp->data + i)->key);
    }
    free(mp->data);
    free(mp);
}

// end of map

/*
(for security reason, strcasecmp is not safe because usage of strtolower which uses heap.)
Compare 2 strings ignoring case
*/
#define strcasecmp(X, Y) (strcmp(strtolwr(X), strtolwr(Y))) == 0

#endif