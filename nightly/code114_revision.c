/*
    (CODE PROGRESS 114, REVISION FROM CODE 113)

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
    I will actually make use of PARSE_INVALID_INPUT
    and changes the way arg_parse_noflag behaves.
*/

// This File indicates the code for 113. Which is a pointer to
// singular flag (-p) switch for future argparser

/*
parts progressed:
    making a revision from previous test (code113)
thoughts:
    missing checks if the NO_SHORTFLAG is specified.
    changes on shorthand_key to fixed size 3
tests:
    [PRECOMPILED]
    (Test 1: NO_SHORTFLAG is tested, should not give any results)
    ./code114 -p "nothing"
    (Test 2: flag '-p' is added, "ptr" shall be returned.)
    ./code114 -p "ptr"
    [COMPILED PROGRAM]
    No test at runtime.
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

#define NO_SHORTFLAG 0

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
    int use_shorthand = short_key != NO_SHORTFLAG;
    char shorthand_key[3];
    if(use_shorthand){
        shorthand_key[0] = arg.flag[0];
        shorthand_key[1] = short_key;
        shorthand_key[2] = '\0';
    }

    // deep-copy the flag and key into stack memory
    size_t total_size = sizeof(char) * 1 + strlen(key) + arg.flag_size;
    char full_key[total_size];
    memset(full_key, 0, total_size);
    // full key
    strncpy(full_key, arg.flag, arg.flag_size);
    strcat(full_key, key);
    
    full_key[total_size] = '\0';

    for(int i = 0; i < arg.argc; i++){
        if(strcmp(arg.argv[i], full_key) == 0 || (strcmp(arg.argv[i], shorthand_key) == 0 && use_shorthand)){
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
    
    char* result = NULL;
    int status = arg_parsestr(env, "pointer", NO_SHORTFLAG, &result);
    if(result == NULL)assert(0);
    if(strcmp(result, "ptr") != 0){
        free(result);
        assert(0);
    }
}
// TEST RESULTS
// [PRECOMPILED]
// Test 1: Passed
// Test 2: Passed
// [COMPILED PROGRAM]
// No test.