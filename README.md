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

commented array_t usage on `standard_class.c` because unstable implementation

enforces easyc.h and other headers to use the 'drop' entity from baseobject.

fixed examples inside `standard.c` For redefining "GET" variable name

typecheck now returns `gthread_t` as uthread (user-level thread)

added `CBITS` or (CPU Bits) entity to baseobject, uses `CHAR_BIT` and pointer size to determine bit, so for example, if your CPU is x86 then the `CBITS` will return 32.

added `trait_` (expands to struct) macro entity to baseobject in order to differentiate structs and traits

renamed `alloc` to `umem` and `alloc_a` to `zmem`, `umem` for uninitialized memory and `zmem` for zero-initialized memory

fixed `map_delete_id` and `map_delete` to cause segmentation fault and memory leaks when given index is 0 and the size is not 1.