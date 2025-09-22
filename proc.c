#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    execlp("ls", "-a", "-l", "-h", NULL);
  }

  else {
    wait(NULL);
    execlp("ls", "-a", NULL);
  }
  return 0;
}
