/*
    (CODE PROGRESS 113, ARGUMENT SINGULAR-FLAG)

        MIT License

    Copyright (c) 2022 syaLikShreer
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

*/

/*
    Future plans:
    So uh I am working at this to use singular flags like in Python,
    this will be done soon (I hope), also I will learn Assembly
    so I can actually make a coroutine header, stack-based though
    this time is not a gthread (Green Thread) and actually lightweight
    but mention that one that makes it not lightweight depends on your arguments needed
    (
        Becoz the arguments is heap-allocated, I can't do anything about it
        or i just have to delete the *_putarg thing to prevent rescaling
    )
    If possible, I'll make them stack'd too
*/

// This File indicates the code for 113. Which is a pointer to
// singular flag (-p) switch for future argparser

/*
parts progressed:
    just started
thoughts:
    adding the char short_key into parsestr, if none, 0 to specify "No short_flag".
    using the first elements of the flag as the short-hand flag
test goal:
    the program is expected to be able to read singular flag
example input:
    [COMPILED PROGRAM]
    (TEST 1: -p short-hand to --pointer)
    ./program_name test_arg -p ptr
    (TEST 2: both flags included)
    ./program_name test_arg -p ptr --pointer ptr
    (TEST 3: --pointer makes the first position)
    ./program_name test --pointer ptr -p ptr
*/

// temporary imports, more imports will be replaced if it contains a copy inside baseobject.h
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define PARSE_ALLOC_FAIL -2 // indicates malloc or similar has failed it's allocation
#define PARSE_NPOS -1 // indicates the position is not found
#define PARSE_POS_EOL -4 // indicates the position is at EOL when parser expects 1 more argument
#define PARSE_OK 0 // indicates parsing has successfully ran without issues
#define PARSE_INVALID_INPUT -6 // nightly error code (for future update)

#define ERR_ERRNO_CONVERSION -5 // indicates the error is coming from errno
#define ERR_NON_NUMERIC_CHAR -3 // indicates the `ENDPTR` does not consume all the string


// the environment to provide argument parser parameters
typedef struct ArgumentsSupplier{
    const int argc; // length of the argv
    const char **argv; // the array consisting of strings argv
    char flag[3]; // store the desired flag (command switch) (if initialized indirectly [via argparser_setenv], the flag will limit to 2 chars)
    size_t flag_size; // the size of ::flag
} argparser_t;

// sets new argparser environment to the instance, returns the argparser instance to caller
argparser_t argparser_setenv(int argc, const char** argv, char* flag){
    argparser_t supplier = {argc, argv};
    char flag_copy[3] = "";
    strncpy(flag_copy, flag, 2);
    flag_copy[strlen(flag)] = '\0';
    // creates a deep copy to supplier.flag while keeping it's stack-memory
    memcpy(supplier.flag, flag_copy, sizeof(char) * strlen(flag_copy));
    supplier.flag_size = strlen(flag_copy);
    return supplier;
}

int arg_findpos(argparser_t arg, char* key, char short_key){
    // deep-copy the flag and short_key into stack memory
    size_t total_shorthand = sizeof(char) * 2 + 1;
    char shorthand_key[total_shorthand];
    memset(shorthand_key, 0, total_shorthand);

    // deep-copy the flag and key into stack memory
    size_t total_size = sizeof(char) * 1 + strlen(key) + arg.flag_size;
    char full_key[total_size];
    memset(full_key, 0, total_size);

    // short-hand key
    shorthand_key[0] = arg.flag[0];
    shorthand_key[1] = short_key;
    shorthand_key[2] = '\0';
    // full key
    strncpy(full_key, arg.flag, arg.flag_size);
    strcat(full_key, key);
    
    full_key[total_size] = '\0';

    for(int i = 0; i < arg.argc; i++){
        if(strcmp(arg.argv[i], full_key) == 0 || strcmp(arg.argv[i], shorthand_key) == 0){
            return i;
        }
    }
    return PARSE_NPOS; // not found
}

int arg_parsestr(argparser_t arg, char* key, char short_key, char** result){
    int get_pos = arg_findpos(arg, key, short_key);
    // if position is not found and the position is at the end of arguments
    if(get_pos == -1){
        return PARSE_NPOS;
    }else if(get_pos == arg.argc - 1){
        return PARSE_POS_EOL;
    }
    *result = (char*)malloc(sizeof(char) * strlen(arg.argv[get_pos + 1]) + 1);
    if(*result == NULL){
        return PARSE_ALLOC_FAIL;
    }
    strcpy(*result, arg.argv[get_pos+1]);
    return PARSE_OK;
}

int main(int argc, const char **argv){
    argparser_t env = argparser_setenv(argc, argv, "--");
    
    char* result;
    int status = arg_parsestr(env, "pointer", 'p', &result);
    if(strcmp(result, "ptr") != 0){
        free(result);
        assert(0);
    }
}
// test results: all passed
// test 1: success
// test 2: success
// test 3: success