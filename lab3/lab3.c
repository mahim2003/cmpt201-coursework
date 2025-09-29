#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5
#define MAX_LEN 1024

void add_line(char *line, char *buffer[], int *idx);
void print_lines(char *buffer[], int count, int idx);

char *my_strdup(const char *s) {
  char *p = malloc(strlen(s) + 1);
  if (p)
    strcpy(p, s);
  return p;
}

int main() {
  char *buffer[MAX_LINES] = {NULL};
  int index = 0;
  char line[MAX_LEN];

  while (1) {
    printf("Enter input: ");
    if (fgets(line, sizeof(line), stdin) == NULL)
      break;

    line[strcspn(line, "\n")] = '\0';
    add_line(my_strdup(line), buffer, &index);

    if (strcmp(line, "print") == 0) {
      print_lines(buffer, MAX_LINES, index);
    }
  }

  for (int i = 0; i < MAX_LINES; i++)
    free(buffer[i]);
  return 0;
}

void add_line(char *line, char *buffer[], int *idx) {
  if (buffer[*idx] != NULL)
    free(buffer[*idx]);
  buffer[*idx] = line;
  *idx = (*idx + 1) % MAX_LINES;
}

void print_lines(char *buffer[], int count, int idx) {
  for (int i = 0; i < count; i++) {
    int pos = (idx + i) % count;
    if (buffer[pos] != NULL)
      printf("%s\n", buffer[pos]);
  }
}
