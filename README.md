# Easy C
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
| Type     | Child_of     | Defined_Name    | Returns   | Side_Note   |
| :------: | :----------: | :-------------: | :-------: | :---------: |
| #define Generic | None         | typecheck       | string    | it checks datatype that's all |
| #define Generic | None  | print           | void      | prints text into your console without formatting |
| function | None         | pwd             | string    | gets current directory |
| function | None         | createConnection | SOCKET(int) | connects to the internet |
| function | None         | getIP (Windows) | string    | get host from name |
| struct   | Subclass     | array_t*        | void      | array class that can holds string (void*) as an element for specific need |
| function | array_t      | array_new       | array_t*  | initialize new array |
| function | array_t      | array_push      | void      | push a new element at end of element |
| function | array_t      | array_insert    | void      | push a new element at specific index of array |
| function | array_t      | array_get       | void *    | get specific value of element |
| function | array_t      | array_get_int   | int *     | get specific value of number element |
| function | array_t      | array_remove    | void      | remove specific index of element |
| function | array_t      | array_print     | void      | prints array to the console    |
| function | array_t      | array_set       | void      | change the specific index of element |
| function | array_t      | array_set_int   | void      | has the same function to array_set, but it's for number element |
| function | None         | tokenize        | array_t*  | split string into array of string tokens |
| function | None         | toLowerCase     | string    | lowercase all string given  |
| function | None         | toUpperCase     | string    | reverse of toLowerCase  |
| function | None         | concat          | string    | concatenates 2 string then return it |
| #define Generic| None   | toString        | string    | stringify the given argument |
| function | None         | toInt           | int       | converts String into int |
| function | None         | toDouble/toFloat | double/float | converts String into float/double |
| function | None         | writeFile/binary | void      | writes a content into a file
| function | None         | readFile/binary  | string    | read the first line of file
| function | None         | readEOF         | void      | read the file lines until EOF, requires callback |
| function | None         | file_line       | int       | get the lines of file |
| function | None         | repstr          | string    | replace specific line of string into a new string |
| function | None         | seed            | void      | sets the random seed, call this ONCE in your main function to properly use rand function |
| function | None         | randint         | int       | returns random number of given argument, requires seed to be called in main function |
| function | None         | randstr         | string    | returns random string of given argument, requires seed to be called in main function |
| function | None         | randstrOptimize | string    | the same with randstr but can set the max and min, requires seed to be called in main function |
| typedef  | char*        | string          | void      | for those whose beginner in C and didn't know String is char * |
| typedef  | __Bool       | bools           | void      | boolean |
| typedef  | uint16_t     | in_port_t       | void      | ports for createConnection in windows |
| #define  | string       | PRINTABLE_CHAR  | string    | console-printable characters |
| #define  | string       | ASCII           | string    | fused of ASCII_LOWER and ASCII_UPPER |
| #define  | string       | ASCII_UPPER     | string    | printable ASCII characters |
| #define  | string       | ASCII_LOWER     | string    | printable ASCII characters |
| #define  | string       | DIGITS          | string    | printable DIGITS characters |
| #define  | string       | SYMBOL          | string    | printable SYMBOLS characters |
| #define  | string       | LENGTH_PRINTABLE| int       | length of printable characters |
| #define  | None         | equals          | bools     | returns whether string 1 is equal in string 2 |


# News
Removed sbs_str_arr and sbs_char_arr function to stabilize warnings, added tables on **Functions and Typedefs** column.
