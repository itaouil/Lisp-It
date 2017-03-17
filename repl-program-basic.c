#include <stdio.h>

// Declare global array of chars
static char input[2048];

int main(int argc, char** argv) {

  // Display some initial information
  puts("List Version 0.1\n");
  puts("Press Ctrl+C to exit\n");

  while(1) {

    // Input to the prompt
    fputs("Lisp> ", stdout);

    // Read input
    fgets(input, 2048, stdin);

    // Print back input
    printf("You prompted: %s\n", input);

  }

  return 0;

}
