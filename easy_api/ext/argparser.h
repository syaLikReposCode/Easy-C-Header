#ifdef STRUCTS
#ifndef _EXT_ARG_PARSER
#define _EXT_ARG_PARSER 1

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define PARSE_ALLOC_FAIL -2 // indicates malloc or similar has failed it's allocation
#define PARSE_NPOS -1 // indicates the position is not found
#define PARSE_POS_EOL -4 // indicates the position is at EOL when parser expects 1 more argument
#define PARSE_OK 0 // indicates parsing has successfully ran without issues
#define PARSE_INVALID_INPUT -6 // nightly error code (for future update)

#define ERR_ERRNO_CONVERSION -5 // indicates the error is coming from errno
#define ERR_NON_NUMERIC_CHAR -3 // indicates the `ENDPTR` does not consume all the string

// checks the return value of strto* based on it's endptr (remaining) or the errno
int error_type(char* endptr){
    if(strlen(endptr) != 0)return ERR_NON_NUMERIC_CHAR;
    if(errno == EINVAL || errno == ERANGE)return ERR_ERRNO_CONVERSION;
    return PARSE_OK;
}

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

// safe get arguments, returns null if the index is below 0 or more than ARGC
const char* arg_get(argparser_t arg, int index){
    if (index < 0 || index >= arg.argc) return NULL;
    return arg.argv[index];
}

// finds the position inside the argv
// returns PARSE_NPOS (PARSE_NO_POSITION) if not found
int arg_findpos(argparser_t arg, char* key){
    // deep-copy the flag and key into stack memory
    size_t total_size = sizeof(char) * 1 + strlen(key) + arg.flag_size;
    char full_key[total_size];

    memset(full_key, 0, total_size);
    strncpy(full_key, arg.flag, arg.flag_size);
    strcat(full_key, key);
    
    full_key[total_size] = '\0';

    for(int i = 0; i < arg.argc; i++){
        if(strcmp(arg.argv[i], full_key) == 0){
            return i;
        }
    }
    return PARSE_NPOS; // not found
}

int arg_parsestr(argparser_t arg, char* key, char** result){
    int get_pos = arg_findpos(arg, key);
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

/* START OF LISTING INTEGER NUMERICAL PARSER */

// parse the i32 number to result
int arg_parsei32(argparser_t arg, char* key, int32_t* result){
    *result = 0;
    int get_pos = arg_findpos(arg, key);
    // if position is not found and the position is at the end of arguments
    if(get_pos == -1){
        return PARSE_NPOS;
    }else if(get_pos == arg.argc - 1){
        return PARSE_POS_EOL;
    }
    char* endptr;
    errno = 0;
    int32_t get_result = (int32_t)strtol(arg.argv[get_pos+1], &endptr, 0);
    int etype = error_type(endptr);
    *result = (etype == PARSE_OK) ? get_result : 0;
    return etype;
}

// parse the i64 number to result
int arg_parsei64(argparser_t arg, char* key, int64_t* result){
    *result = 0;
    int get_pos = arg_findpos(arg, key);
    // if position is not found and the position is at the end of arguments
    if(get_pos == -1){
        return PARSE_NPOS;
    }else if(get_pos == arg.argc - 1){
        return PARSE_POS_EOL;
    }
    char* endptr;
    errno = 0;
    int64_t get_result = (int64_t)strtoll(arg.argv[get_pos+1], &endptr, 0);
    int etype = error_type(endptr);
    *result = (etype == PARSE_OK) ? get_result : 0;
    return etype;
}

/* END OF LISTING INTEGER NUMERICAL PARSER */

int arg_parsefloat(argparser_t arg, char* key, float* result){
    int get_pos = arg_findpos(arg, key);
    // if position is not found and the position is at the end of arguments
    if(get_pos == -1){
        return PARSE_NPOS;
    }else if(get_pos == arg.argc - 1){
        return PARSE_POS_EOL;
    }
    char* endptr;
    errno = 0;
    float get_result = strtof(arg.argv[get_pos+1], &endptr);
    int etype = error_type(endptr);
    *result = (etype == PARSE_OK) ? get_result : 0;
    return etype;
}

int arg_parsedouble(argparser_t arg, char* key, double* result){
    int get_pos = arg_findpos(arg, key);
    // if position is not found and the position is at the end of arguments
    if(get_pos == -1){
        return PARSE_NPOS;
    }else if(get_pos == arg.argc - 1){
        return PARSE_POS_EOL;
    }
    char* endptr;
    errno = 0;
    double get_result = strtod(arg.argv[get_pos+1], &endptr);
    int etype = error_type(endptr);
    *result = (etype == PARSE_OK) ? get_result : 0;
    return etype;
}

// (don't misconcept parsebool with parseint)
// parses bool without extra argument, it is used to check if the key is present in the argv
int arg_parsebool(argparser_t arg, char* key, int* result){
    int pos = arg_findpos(arg, key);
    *result = pos != PARSE_NPOS;
    return PARSE_OK;
}

// get the first argument that is present without a flag
// will search for the next non-flagged argv if exclude is not null
int arg_parse_noflag(argparser_t arg, char** result, char* exclude){
    for(int i = 1; i < arg.argc; i++){
        if(strstr(arg.argv[i], arg.flag) == NULL){
            // exclude detected
            if(exclude != NULL && strcmp(arg.argv[i], exclude) == 0)continue;
            *result = malloc(sizeof(char) * strlen(arg.argv[i]) + 1);
            if(*result == NULL){
                return PARSE_ALLOC_FAIL;
            }
            strcpy(*result, arg.argv[i]);
            return PARSE_OK;
        }
    }
    *result = NULL;
    return PARSE_NPOS;
}

#endif
#endif