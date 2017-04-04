#include "mpc.h"
#include <stdio.h>
#include <stdlib.h>

// Handle WIN32 Operating System
#ifdef _WIN32
#include <string.h>

// Array of char
static char buffer[2048];

char* readline(char* prompt) {

    // Output to console
    fputs(prompt, stdout);

    // Read input from console
    fgets(buffer, 2048, stdin);

    // Create a tmp storage (same size as buffer)
    char* cpy = malloc(strlen(buffer) + 1);

    // Copy
    strcpy(cpy, buffer);

    cpy[strlen(cpy) - 1] = '\0';

    return cpy;

}

void add_history(char* nothing) {}

// If not WIN32 OS handle differently
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

// Main
int main(int argc, char* argv) {

    // Parsers
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("lispy");

    // Define Parsers
    mpca_lang(MPCA_LANG_DEFAULT,
        "
                                                                  \
            number      : /-?[0-9]+/;                             \
            operator    : '+' | '-' | '*' | '/';                  \
            expr        : <number> | '(' <operator> <expr> ')';   \
            lispy       : /^/ <operator> <expr>+ /$/;
        ",
        Number, Operator, Expr, Lispy);

    puts("Lisp V2.2");
    puts("Press CTRL+C to exit program");

    while(1) {

        // Read user input
        char* input = readline("lisp> ");
        add_history(input);

        // Use parser to process input
        mpc_result_t r;
        if(mpc_parse("<stdin>", input, Lispy, &r)) {
            // On success, print and delete AST
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        }

        else {
            // On failure, print and delete error stacktrace
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        // Free memory created by readline
        free(input);
    }

    // Delete parser
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;

}

//cc -std=c99 -Wall parsing.c mpc.c -ledit -lm -o parsing