#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT 256

int main() {
  char input[MAX_INPUT];

  printf("Enter programs to run.\n");

  while (1) {
    printf("> ");
    if (fgets(input, sizeof(input), stdin) == NULL)
      break;

    for (int i = 0; input[i]; i++) {
      if (input[i] == '\n')
        input[i] = '\0';
    }

    pid_t pid = fork();
    if (pid == 0) {
      execl(input, input, (char *)NULL);
      printf("Exec failure\n");
      return 1;
    } else {
      waitpid(pid, NULL, 0);
    }
  }
  return 0;
}
