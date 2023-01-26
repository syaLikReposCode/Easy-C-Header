# Easy C
(REWRITE: easyc.h is being rewritted, old easyc needs to import 'old_easyc.h')

(old Easy C was considered unsafe and spaghetti code)

some random Header that might helps your C coding, how to use it? simply add
```c
#include "Easy_C/easyc.h"
```
to your C code.

# License
this project was licensed under the terms of MIT License

# Target and Notes
this Header targets for simplicity and ease-of-use for your programs (NOTE: this is for **C ONLY**, do not try include this header on C++ code)

# Version
header currently version 1.0 beta

# Written
this Header is written completely using ANSI C (standardized C) (except for the file inside `ext` folder)

# Functions, Parameters and Typedefs
**[NON-STRUCT TYPE]**

| Name Type  | Child of     | Defined Name    | Returns   | functionality   |
| :--------: | :----------: | :-------------: | :-------: | :------------:  |
| Macro Generic | base      | typecheck       | char*     | checks type data |
| Macro Generic | base      | print           | none      | prints with type inference |
| Macro Generic | base      | println         | none      | like print but it adds newline |
| function   |  base        | strtolwr        | char*     | makes string to lower |
| function   |  base        | strtoupper      | char*     | reverse strtolwr |
| function   |  base        | repstr          | char*     | replace found string with new string|
| function   |  base        | randint         | int       | generates pseudo-random int (seed call required) |
| function   |  base        | randstr         | char*     | utilizes randint to generate random string  (seed call required) |
| function   | base         | seed            | none      | set pseudo-random seed |
| Macro Constant | base     | ALL             | none      | all keyboard-writable characters |
| Macro Constant | base     | LETTERS         | none      | fusion of ascii upper and lower |
| Macro Constant | base     | ASCII_UPPER     | none      | uppercase of ascii_lower |
| Macro Constant | base     | ASCII_LOWER     | none      | lowercase of ascii_upper |
| Macro Constant | base     | DIGITS          | none      | printable digits         |
| Macro Constant | base     | SYMBOL          | none      | punctuation              |
| function       | base     | strcmpcase      | int       | compares 2 string ignoring the case |
| function       | base     | kernel_name     | char*     | get kernel names |

**[STRUCT TYPE (need STRUCTS macro to access)]**
| Name Type  | Child of     | Defined Name    | Returns   | functionality   |
| :--------: | :----------: | :-------------: | :-------: | :------------:  |
| struct     | base         | iterator_t      | none      | base structure for iterator |
| function   | iterator_t   | iterator_create | iterator_t| create iterator for registered data |
| struct     | base         | array_t         | none      | base structure for dynamic-array |
| function   | array_t      | array_new       | array_t*  | initializes empty array_t |
| function   | array_t      | array_push      | none      | push new element to array_t |
| function   | array_t      | array_get       | void*     | get element by index |
| function   | array_t      | array_print     | none      | pretty-print array |
| function   | array_t      | array_insert    | none      | insert element at specific index |
| function   | array_t      | array_get_int   | none      | get element by index but returns number |
| function   | array_t      | array_remove    | none       | remove element by index |
| function   | array_t      | drop            | none       | frees array_t struct |
| function   | array_t      | array_set       | none       | change value of index |
| function   | array_t      | array_set_int   | none       | array_set but for number |
| struct     | base         | pair_t          | none       | type-structure for key-value operations.  |
| function   | pair_t       | pair_make       | pair_t*    | make new pair in heap     |
| function   | pair_t       | pair_create     | pair_t     | make new pair in stack |
| function   | pair_t       | drop            | void       | drops pair returned by pair_make    |
| struct     | base         | map_t           | none       | base structure for map |
| function   | map_t        | map_new         | map_t*     | initializes new empty map |
| function   | map_t        | map_insert      | none       | inserts new key-value element |
| function   | map_t        | map_get         | void*      | get element by index |
| function   | map_t        | map_find        | void*      | get element by keyname |
| function   | map_t        | map_set         | void       | set new value to key |
| function   | map_t        | drop            | void       | drops map from heap |
| function   | map_t        | map_print       | void       | prints map in JSON format |
| function   | map_t        | map_delete      | void       | delete key from map |
| function   | map_t        | map_delete_id   | void       | delete index from map |
| function   | base         | drop            | void       | frees any data  |

**[FUNCTION PARAMETERS]**
| Defined Name      |         Parameters             |
| :---------------: | :----------------------------: |
| typecheck         | Generic Template               |
| print & println   | Generic  Template              |
| strtolower        | char* str                      |
| strtoupper        | char* str                      |
| repstr            | char* str, char* f, char* n    |
| seed              | None (void)                    |
| randint           | int min, int m                 |
| randstr           | char* sup, int len             |
| strcmpcase        | char* s1, int s2               |
| kernel_name       | None (void)                    |
| kernel_name       | None (void)                    |
| next_default      | iterator_t* it                 |
| has_next_default  | iterator_t it                  |
| create_default    | Generic Template               |
| create_default    | Generic Template               |
| array_new         | int elementSize                |
| array_get         | array_t* this, int idx         |
| array_push        | array_t* this, void* elem      |
| drop (array)      | array_t* this                  |
| array_get_int     | array_t* this, int idx         |
| array_remove      | array_t* this, int idx         |
| array_insert      | array_t* a, int idx, void* e   |
| array_print       | array_t* this                  |
| array_set         | array_t* th, int idx, void* e  |
| array_set_int     | array_t* th, int idx, int el   |
| pair_make         | char* key, void* value         |
| pair_create       | char* key, void* value         |
| drop (pair)       | pair_t* this                   |
| map_new           | None (void)                    |
| next (map_t)      | iterator_t* instance           |
| has_next (map_t)  | iterator_t instance            |
| create (map_t)    | map_t* instance                |
| map_insert        | map_t* this, char* k, void* v  |
| map_index         | map_t* this, char* key         |
| map_get           | map_t* this, size_t idx        |
| map_find          | map_t* this, char* k           |
| map_set           | map_t* this, char* k, void* nv |
| map_print         | map_t* this                    |
| map_move          | map_t* mp, size_t i, size_t j  |
| map_delete_id     | map_t* this, size_t i          |
| map_delete        | map_t* this, char* k           |
| drop (map_t)      | map_t* this                    |
| drop (base)       | None (void)                    |


# News
Welcome to Beta phase, I will focus to add more APIs than standard easyc.h for now, easyc.h will uncommonly get new updates, APIs are provided in the "Easy_C/ext" folder


Simple concurrent handling, coroutine! How to get them? Add this code to your file:

```c
#define STRUCTS
#include "Easy_C/ext/coroutine.h"
```

After that you just unlocked the *coroutine_t* struct and it's functions!

(Coroutines are in testing, I'm not sure to include it in easyc.h standard, so I make an ext folder for external APIs.)

added examples folder for usage

renamed destroy to drop, and base_destroy now just frees memory

added string (char*) iterator type

Added Macro Guard to prevent file conflict

Drop macro support for coroutines

Added if preprocessor closure to determine struct and coroutine availability

Fixed println, print, and typecheck doesn't work not defining STRUCTS

Modified kernel_name to properly checks if it's windows or other kernel

Fixed map_delete_id, and map_delete cannot delete map when the size is 1