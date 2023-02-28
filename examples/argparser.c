/*
    EXAMPLE FILE
    This example teach you how to make a CLI (Command-Line-Interface) program
    with the argparser API provided by Easy C!
    First off, import it, and as usual, argparser is STRUCTS-only interface!
*/
#define STRUCTS
#include "../easy_api/ext/argparser.h"
#include <string.h> // strcmp
#include <stdio.h> // printf, fprintf, stderr, fopen, fclose

// now you just unlocked the argparser_t environment! let's define main
// you would need to specify argc and argv in the main

void error(const char* msg){
    fprintf(stderr, "%s\n", msg);
    exit(1); // stdlib.h (already defined in argparser.h)
}

// let's create an error handler
#define check_err(status) switch(status){ \
        case ALLOC_FAIL: \
        error("Failed to get the result of type, unable to allocate memory"); \
        break; \
        case PARSE_NPOS: \
        error("No flag arguments specified, (use --help to show available switch)"); \
        break; \
        case LPOS_EOL: \
        error("Expected arguments after flag, but got none"); \
        break; \
        case PARSE_INVALID_INPUT: \
        error("Expected arguments but got another flag"); \
        break; \
   }

int main(int argc, const char* argv[]){
    // now initialize the environment
    argparser_t env = argparser_setenv(argc, argv, "--"); // here I used "--" flag for the example
    /*
    all set! Let's create a program that can manipulate files
    combination of echo "CONTENT" > file, cat and touch!
    */
   // let's define which user specify it.
    char* op_type;
    int status = arg_parsestr(env, "operation", 'p', &op_type);
   // we need the status that arg_parsestr returns to create a robust app!
    check_err(status);
    // the expected of op_type can be this arguments:
    // "./your_program --operator wr" or "./your_program -p wr"
    // let's give a logic to our app
    if(strcmp(op_type, "wr") == 0){
        // freeing op_type as it's no longer needed (why so early? Because when check_err is not OK, it immediately exits
        // and op_type left not freed, which causes memory leak!)
        free(op_type);
        // getting the file, expected program arguments: ./program [FILE] [SWITCH]
        char* get_file;
        status = arg_parse_noflag(env, &get_file, 0); // get the first non-flag parameter
        check_err(status);
        // getting contents, expected program arguments: ./program [FILE] --content "content" or ./program [FILE] -s "content"
        char* contents; 
        status = arg_parsestr(env, "content", 's', &contents); // get the second flag
        // in case if the check_err is not OK.
        if(status != OPOK)free(get_file);
        check_err(status);
        FILE* fp = fopen(get_file, "w");
        fprintf(fp, "%s\n", contents);
        fclose(fp);
        free(get_file);
        free(contents);
    }
    // if our user wanted to read
    else if(strcmp(op_type, "rd") == 0){
        free(op_type);
        char* get_file;
        status = arg_parse_noflag(env, &get_file, 0);
        check_err(status);
        int get_buf; // specify buffer for the read
        status = arg_parsei32(env, "buf", 'c', &get_buf); // no more.
        if(status != OPOK)free(get_file); // in case error
        check_err(status);
        // allocate memory for get_buf
        char* contents = calloc(get_buf + 1, sizeof(char));
        /* breakdowns:
        sizeof(char): Returns the size for char, different OS or CPU may have different size of CHAR
        get_buf: The buffer specified by user
        1: For string null-terminator
        */
       // checks whether the contents successfully allocated
       if(contents == NULL){
            error("Failed to allocate memory");
       }
       FILE* fp = fopen(get_file, "r");
       fgets(contents, get_buf, fp);
       printf("Your content is: %s\n", contents);
       fclose(fp);
       // free app
       free(contents);
       free(get_file);
    }
    // if our user wanted to create
    else if(strcmp(op_type, "cr") == 0){
        free(op_type);
        char* file_type;
        status = arg_parse_noflag(env, &file_type, 0);
        check_err(status);
        FILE* fp = fopen(file_type, "w");
        fclose(fp);
        free(file_type);
    }
    printf("Thanks for using my program!\n");
    return 0;
}
/*
    Now to test your program, you can use this following example:
    creating file
    ./program myfile.txt --operation cr
    reading file
    ./program myfile.txt --operation rd --buf 30
    writing file
    ./program myfile.txt --operation wr --content "Hello, world!"

    (shortflag version)
    creating file
    ./program myfile.txt -p cr
    reading file
    ./program myfile.txt -p rd -c 30
    writing file
    ./program myfile.txt -p wr -s "Hello, world!"
    
    END OF EXAMPLE
    That's how you create a CLI App using this header,
    although it has some fallbacks it gets the job done,
    I hope this helps!
    Thanks for reading!
*/

/*
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