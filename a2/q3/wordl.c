#include <stdio.h>
#include <string.h>
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s word\n", argv[0]);
    return 1;
  }
  // theWord is not a pointer to a string that stores the command line argument word that was provided.
  char *theWord = argv[1];
}