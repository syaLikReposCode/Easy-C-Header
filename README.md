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

**Functions**
repstr, toLowerCase, toUpperCase, concat, printString/char/int/double, toInt, toDouble, toFloat, writeFile, readFile, writeBinary, readBinary, rm, readEOF, createConnection (windows/linux), getIP (windows), sbs_char_arr, sbs_str_arr (unstable), input, tokenize, randint, seed, randstr, randstrOptimize


**Preprocessor Functions**
equals, typecheck, println, print, toString

**Typedefs**
string (expands to: char pointer), bools (expands to: underscore_Bool), in_port_t (expands to: u_int16_t [windows])

**Structs**
[classes: array_t] [functions: array_push, array_size, array_print, array_get, array_get_int, array_destroy, array_insert, array_remove, array_new]

# News
added struct array_t, new function: randint, seed, randstr, randstrOptimize, tokenize,
added new constants: ASCII, ASCII_UPPER, ASCII_LOWER, DIGITS, SYMBOLS, PRINTABLE_CHAR, LENGTH_PRINTABLE
