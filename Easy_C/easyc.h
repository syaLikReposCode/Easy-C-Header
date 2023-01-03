// WARNING! THIS HEADER IS FOR C ONLY! DO NOT INCLUDE THIS HEADER WITH C++
// for C++ please use the .hpp version [Coming Soon]
#define AUTHOR "syaLikShreer"
#define EASY_C_VERSION "2.2a"
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
                              char*: "char_memory",\
                              char: "character", \
                              double: "double", \
                              float: "float", \
                              long: "long",\
                              short: "short", \
                              void*: "memory", \
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

void printMemory(void* arg){
    printf("%s", (char*)arg);
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
                                void*: printMemory, \
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
void printMemoryLn(void* arg){
    printf("%s\n", (char*)arg);
}

#define println(X) _Generic((X), int: printIntln, \
                              _Bool: printBoolln, \
                              char*: printStringln,\
                              char: printCharln, \
                              double: printDoubleln, \
                              long double: printLongDbln, \
                              float: printFloatln, \
                              size_t: printIntln, \
                              void*: printMemoryLn, \
                               default: printNoneln)(X)

bool b = false;

// returns lowered string, stored in heap [heap]
char* strtolower(char* str){
    char* res = (char*)malloc(strlen(str) + 1);
    strcpy(res, "");
    for(int i = 0; i < strlen(str); i++){
        res[i] = tolower(str[i]);
    }
    res[strlen(str)] = '\0';
    return res;
}
// returns upper string, stored in heap [heap]
char* strtoupper(char* str){
    char* res = (char*)malloc(strlen(str) + 1);
    strcpy(res, "");
    for(int i = 0; i < strlen(str); i++){
        res[i] = toupper(str[i]);
    }
    res[strlen(str)] = '\0';
    return res;
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

// compares 2 string ignoring case
int strcmpcase(char* st1, char* st2){
    char* lw = strtolower(st1);
    char* l2w = strtolower(st2);
    int cmp = strcmp(lw, l2w);
    free(lw);
    free(l2w);
    return cmp;
}


#ifdef STRUCTS
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


// independent-type pair.
typedef struct{
    char* key;
    void* value;
} pair_t;

pair_t* pair_make(char* key, void* value){
    pair_t* pair = (pair_t*)malloc(sizeof(pair_t));
    pair->key = malloc(strlen(key) + 1);
    pair->value = malloc(strlen(value));
    strcpy(pair->key, key);
    memcpy(pair->value, value, strlen(value));
    return pair;
}

void pair_destroy(pair_t* pair){
    free(pair->key);
    free(pair->value);
    free(pair);
}

// begin of map

// map type, utilizes heap storage for use
typedef struct{
    pair_t** data;
    size_t size;
} map_t;

// initializes empty map
map_t* map_new(){
    map_t* map;
    map = malloc(sizeof(map_t));

    map->size = 0;
    map->data = NULL;
    return map;
}

// inserts new element to the map
void map_insert(map_t* mp, char* key, void* value){
    if(mp->size == 0)
        mp->data = malloc(sizeof(pair_t));
    else
        mp->data = realloc(mp->data, sizeof(pair_t) * (mp->size + 1));
    
    mp->data[mp->size++] = pair_make(key, value);
}

// get map index by key (used on map_set and map_find)
long map_index(map_t* mp, char* k){
    for(size_t i = 0; i < mp->size; i++){
        if(strcmp(k, mp->data[i]->key) == 0){
            return i;
        }
    }
    return -2;
}

// retrieves map data by index (faster than map_find)
void* map_get(map_t* mp, size_t idx){
    if(idx >= mp->size)return NULL;
    return mp->data[idx]->value;
}

// retrieves map data by key
void* map_find(map_t* mp, char* key){
    size_t idx = map_index(mp, key);
    if(idx == -2)return NULL;
    return mp->data[idx]->value;
}

void map_set(map_t* mp, char* key, void* nval){
    size_t idx = map_index(mp, key);
    if(idx == -2)return;
    mp->data[idx]->value = realloc(mp->data[idx]->value, sizeof(pair_t) * strlen(nval));
    memcpy(mp->data[idx]->value, nval, strlen(nval));
}

// destroy map and it's data
void map_destroy(map_t* mp){
    for(size_t i = 0; i < mp->size; i++){
        pair_destroy(mp->data[i]);
    }
    free(mp->data);
    free(mp);
}

// end of map

#endif