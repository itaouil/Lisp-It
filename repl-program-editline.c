#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/add_history.h>

int main(int argc, char** argv) {

  puts("List Version 0.2\n");
  puts("Press Ctrl+C to exit\n");

  while(1) {

    // Read input via readline
    char* input = readline("Lisp> ");

    // Record input
    add_history(input);

    // Print input
    printf("You prompted: %s\n", input

    // Free allocated memory (by readline)
    free(input);

  }

  return 0;

}
