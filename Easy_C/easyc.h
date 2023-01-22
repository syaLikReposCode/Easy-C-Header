// WARNING! THIS HEADER IS FOR C ONLY! DO NOT INCLUDE THIS HEADER WITH C++
#define AUTHOR "syaLikShreer"
#define EASY_C_VERSION "2.4a"
// standard library import
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
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
                              map_t*: "map",\
                              array_t*: "array",\
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
void printNone(void){
    printf("%s", "");
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

void printLong(long long b){
    printf("%lld", b);
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
                              long long: printLong, \
                              long: printLong, \
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
void printNoneln(void){
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
void printLongln(long long arg){
    printf("%lld\n", arg);
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
                              long long: printLongln, \
                              long: printLongln, \
                              float: printFloatln, \
                              size_t: printIntln, \
                              void*: printMemoryLn, \
                               default: printNoneln)(X)

bool b = false;

// returns lowered string, stored in heap [heap]
char* strtolower(char* str){
    char* res = (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(res, "");
    for(int i = 0; i < strlen(str); i++){
        res[i] = tolower(str[i]);
    }
    res[strlen(str)] = '\0';
    return res;
}
// returns upper string, stored in heap [heap]
char* strtoupper(char* str){
    char* res = (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(res, "");
    for(int i = 0; i < strlen(str); i++){
        res[i] = toupper(str[i]);
    }
    res[strlen(str)] = '\0';
    return res;
}

// replaces string if found [heap]  (100 chars max)
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

// returns an kernel_name, "darwin" for mac, "linux" for linux, "nt" for a fallback option (any os)
// "any" is rarely returned
char* kernel_name(){
    int code = system("uname -s > os.txt");
    if(code != 0){
        return "nt";
    }
    int size = 1;
    FILE* fp = fopen("os.txt", "r");
    char c = fgetc(fp);
    while(c != '\n' && c != EOF){
        c = fgetc(fp);
        size++;
    }
    if(fseek(fp, 0, SEEK_SET) != 0){
        fprintf(stderr, "fail to fetch kernel_name, cursor cannot be moved\n");
        return NULL;
    }
    char* g = (char*)calloc(size+1, sizeof(char));
    fgets(g, size, fp);
    fclose(fp);
    if(remove("os.txt") != 0){
        fprintf(stderr, "Output of os.txt cannot be deleted continuing...");
    }
    if(strcmpcase(g, "darwin") == 0){
        free(g);
        return "darwin";
    }else if(strcmpcase(g, "linux") == 0){
        free(g);
        return "linux";
    }
    free(g);
    return "any";
}



#ifdef STRUCTS
// base structure for any types that requires iterator
typedef struct iterator_trait{
    void* group;
    void* value;
    size_t pos;
    void (*next)(struct iterator_trait*);
    int (*has_next)(struct iterator_trait);
} iterator_t;

// if struct does not implement trait (iterator_has_next) macro
int iterator_has_next_default(iterator_t iter){
    return 0;
}
// if struct does not implement trait (iterator_next) macro
void iterator_next_default(iterator_t* iter){}
// if struct does not implement trait (iterator_create) macro
iterator_t iterator_create_default(void){
    iterator_t it;
    it.group = NULL;
    it.pos = 0;
    it.value = NULL;
    return it;
}

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

// create heap-based memory pair
pair_t* pair_make(char* key, void* value){
    pair_t* pair = (pair_t*)malloc(sizeof(pair_t));
    pair->key = calloc(strlen(key) + 1, sizeof(char));
    pair->value = calloc(strlen(value), sizeof(char));
    strcpy(pair->key, key);
    memcpy(pair->value, value, strlen(value));
    return pair;
}

// create stack-based memory pair
pair_t pair_create(char* key, void* value){
    pair_t pair;
    pair.key = key;
    pair.value = value;
    return pair;
}

// frees heap memory returned by pair_make
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

// map iterator trait implementor

int map_iterator_has_next(iterator_t iter){
    return iter.pos < ((map_t*)iter.group)->size;
}

void map_iterator_next(iterator_t* iter){
    if(iter->pos > ((map_t*)iter->group)->size)return;
    iter->pos++;
    iter->value = ((map_t*)iter->group)->data[iter->pos];
}

iterator_t map_iterator_create(map_t* mp){
    iterator_t it;
    it.pos = 0;
    it.group = mp;
    it.value = mp->data[0];
    it.next = map_iterator_next;
    it.has_next = map_iterator_has_next;
    return it;    
}

// end iterator trait implementor


// inserts new element to the map
void map_insert(map_t* mp, char* key, void* value){
    if(mp->size == 0)
        mp->data = malloc(sizeof(pair_t));
    else
        mp->data = realloc(mp->data, sizeof(pair_t) * (mp->size + 1));
    mp->data[mp->size++] = pair_make(key, value);
}

// get map index by key
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

// set new map value
void map_set(map_t* mp, char* key, void* nval){
    size_t idx = map_index(mp, key);
    if(idx == -2)return;
    mp->data[idx]->value = realloc(mp->data[idx]->value, sizeof(pair_t) * strlen(nval));
    memcpy(mp->data[idx]->value, nval, strlen(nval));
}

// print map to stdout
void map_print(map_t* mp){
    printf("{");
    int first = 1;
    for(iterator_t it = map_iterator_create(mp); it.has_next(it); it.next(&it)){
        if(!first)printf(", ");
        pair_t* p = (pair_t*)it.value;
        printf("\"%s\": \"%s\"", p->key, (char*)p->value);
        first = 0;
    }
    printf("}");
}

// move / swap elements of pos1 and pos2
void map_move(map_t* mp, size_t pos1, size_t pos2){
    if(pos2 > mp->size || pos1 > mp->size)return;
    
    pair_t temp;
    memcpy(&temp, mp->data[pos1], sizeof(pair_t));
    memcpy(mp->data[pos1], mp->data[pos2], sizeof(pair_t));
    memcpy(mp->data[pos2], &temp, sizeof(pair_t));
}

void map_delete_id(map_t* mp, size_t at){
    if(mp->size == 0)return;
    for(size_t i = at; i < mp->size - 1; i++){
        map_move(mp, i, i + 1);
    }
    pair_destroy(mp->data[mp->size-1]);
    mp->data = realloc(mp->data, sizeof(pair_t) * (mp->size - 1));
    mp->size--;
}

// O(n^2) -> index finding which is log n
void map_delete(map_t* mp, char* key){
    if(mp->size == 0)return;
    long idx = map_index(mp, key);
    if(idx == -2)return;
    
    for(size_t i = idx; i < mp->size - 1; i++){
        map_move(mp, i, i + 1);
    }
    pair_destroy(mp->data[mp->size-1]);
    mp->data = realloc(mp->data, sizeof(pair_t) * (mp->size - 1));
    mp->size--;
}

// frees map from heap
void map_destroy(map_t* mp){
    for(size_t i = 0; i < mp->size; i++){
        pair_destroy(mp->data[i]);
    }
    free(mp->data);
    free(mp);
};

// end of map

void base_destroy(void){}

// iterator class member
#define iterator_create(T) _Generic((T),\
    map_t*: map_iterator_create, \
    default: iterator_create_default\
)(T)

// generic macro applied to every structs, plays as destructor for each structs
#define destroy(T) _Generic((T),\
    array_t*: array_destroy,\
    pair_t*: pair_destroy, \
    map_t*: map_destroy,\
    default: base_destroy\
)(T)


#endif
