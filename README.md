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
this Header still in Alpha builds, there might be some of bugs and complexity on using functions, i'm gonna improve that later

# Written
this Header is *almost* completely using ANSI C (standardized C)

# Functions and Typedefs
**[SAFE TYPE]**

| Name Type  | Child of     | Defined Name    | Returns   | functionality   |
| :--------: | :----------: | :-------------: | :-------: | :------------:  |
| Macro Generic | base      | typecheck       | char*     | checks type data |
| Macro Generic | base      | print           | none      | prints with type inference |
| Macro Generic | base      | println         | none      | like print but it adds newline |
| function   |  base        | strtolwr        | char*     | makes string to lower |
| function   |  base        | strtoupper      | char*     | reverse strtolwr |
| function   |  base        | repstr          | char*     | replace found string with new string|
| function   |  base        | randint         | int       | generates pseudo-random int (seed call required) |
| function   |  base        | randstr         | char*     | utilizes randint to generate random string  (seed call required |
| function   | base         | seed            | none      | set pseudo-random seed |
| Macro Constant | base     | ALL             | none      | all console-printable characters |
| Macro Constant | base     | LETTERS         | none      | fusion of ascii upper and lower |
| Macro Constant | base     | ASCII_UPPER     | none      | uppercase of ascii_lower |
| Macro Constant | base     | ASCII_LOWER     | none      | lowercase of ascii_upper |
| Macro Constant | base     | DIGITS          | none      | printable digits         |
| Macro Constant | base     | SYMBOL          | none      | punctuation              |
| Macro Constant | base     | strcasecmp      | _Bool     | compares 2 string ignoring the case |

**[UNSAFE TYPE (need UNSAFE_LOCK macro to access)]**
| Name Type  | Child of     | Defined Name    | Returns   | functionality   |
| :--------: | :----------: | :-------------: | :-------: | :------------:  |
| struct     | base         | array_t         | none      | base structure for dynamic-array |
| function   | array_t      | array_new       | array_t*  | initializes empty array_t |
| function   | array_t      | array_push      | none      | push new element to array_t |
| function   | array_t      | array_get       | void*     | get element by index |
| function   | array_t      | array_print     | none      | pretty-print array |
| function   | array_t      | array_insert    | none      | insert element at specific index |
| function   | array_t      | array_get_int   | none      | get element by index but returns number |
| function   | array_t      | array_remove    | none       | remove element by index |
| function   | array_t      | array_destroy   | none       | frees array_t struct |
| function   | array_t      | array_set       | none       | change value of index |
| function   | array_t      | array_set_int   | none       | array_set but for number |
| struct     | base         | data_list       | none       | used on map    |
| struct     | base         | map_t           | none       | base structure for map |
| function   | map_t        | map_new         | map_t*     | initializes new empty map |
| function   | map_t        | map_insert      | none       | inserts new key-value element |
| function   | map_t        | map_get         | void*      | get element by index |
| function   | map_t        | map_find        | void*      | get element by keyname |
| function   | map_t        | map_destroy     | none       | frees map |

# News
Rewrite old_easyc.h, some functions are removed because it's unsafe behavior.

unsafe functions now requires macro UNSAFE_LOCK to access such as map, array, and other heap-based functions
