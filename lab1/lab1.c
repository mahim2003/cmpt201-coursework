#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  char *line = NULL;
  size_t len = 0;
  printf("Please enter some text: ");
  getline(&line, &len, stdin);
  char *saveptr = NULL;
  char *result = strtok_r(line, " ", &saveptr);
  while (result != NULL) {
    printf("%s\n", result);
    result = strtok_r(NULL, " ", &saveptr);
  }
  free(line);
}
