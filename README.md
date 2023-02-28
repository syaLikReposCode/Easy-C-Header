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
header currently version 1.6 beta

# Written
the entire header (including Exclusive API) is written in pure Standard C11 (Some Exclusive APIs in the future may use non-standard function)

# News
Welcome to Beta phase, I will focus to add more APIs than standard easyc.h for now, easyc.h will uncommonly get new updates, APIs are provided in the `easy_api/ext` folder

small changes:

    added readline function in the standard, examples and the doc_table aswell.

    support for short flag in argparser

    argparser example now has an example for short flag

    added `arg_checkflag` to check if the input is standalone or a flag input

    added `LPOS_EOL, ALLOC_FAIL, OPOK` constants entity on baseobject error code.

    added `_THROWABLE` in baseobject indicating the entire classes (usually this marked onto the struct), or functions does not implement robust option yet. (it does nothing)

    added `_ANCIENT_FEATURE` if the implementation still uses v1 (this will get removed if there are no v1 features available)