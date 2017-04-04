//Example of what pre-processor looks like in C

// Include common libraries
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

    while(1) {
        puts("Lisp V2.2");
        puts("Press CTRL+C to exit program");

        char* input = readline("lisp> ");

        add_history(input);

        free(input);
    }

    return 0;

}