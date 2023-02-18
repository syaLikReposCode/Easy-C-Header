# Easy C
(REWRITE: easyc.h is being rewritted, old easyc needs to import 'old_easyc.h')

(old Easy C was considered unsafe and spaghetti code)

some random Header that might helps your C coding, how to use it?

First Get Git Source-Code-Management (SCM) at [This link](https://git-scm.com)

Second, do the command
```bash
git clone https://github.com/syaLikReposCode/Easy-C-Header
```

Third, copy easyc.h and baseobject.h or the entire `easy_api/` folder to your project

Done! Now you can import the standard API (easyc.h) in your C code:
```c
#include "easy_api/easyc.h"
```

Or Exclusive APIs (ext) in your project!

**FAST WAY**

Go to easy_api/easyc.h and easy_api/baseobject.h, copy all the contents and store it in the .h file extension in your project, now you can import the need of your project

(Why must baseobject.h copied too? Because easyc.h uses some member functions from baseobject.h)

# License
this project was licensed under the terms of MIT License

# Target and Notes
this Header targets for simplicity and ease-of-use for your programs (NOTE: this is for **C ONLY**, do not try include this header on C++ code), and also for beginners!

For Beginners, Learn how the function works, then I'm sure you will understand how it works

For Experts, Sorry this is not for you! The implementation is not optimized or efficient in any way, if you're willing to improve it, fork it and pull request!

# Version
header currently version 1.5 beta

# Written
the entire header (including Exclusive API) is written in pure Standard C11 (Some Exclusive APIs in the future may use non-standard function)

# News
Welcome to Beta phase, I will focus to add more APIs than standard easyc.h for now, easyc.h will uncommonly get new updates, APIs are provided in the `easy_api/ext` folder

makes group in iterator field readonly

fixed typo

moved the **Functions, Parameters and Typedefs** section to `doc_table/` folder (this took time to move, not even Exclusive APIs are included yet)

renamed main folder `Easy_C/` to `easy_api/`

argument parsers! (view the file `examples/argparser.c` for more info!)

renamed ASCII_UPPER/LOWER to WORD_LOWER/UPPER

renamed coroutine to gthread because inaccuracy name due to memory overhead (coroutine.h -> greenthread.h)

added nightly code (experimental) folder in `nightly/`, it's where I kept my progress tracked

added sdrop and rdrop macro on baseobject entity

renamed drops to hdrop (heap-drop) to make a reasonable drop variant