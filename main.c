#include "containers.h"
#include "hello.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Buffer* read_from_fd(FILE* fd) {
  //
  return NULL;
}

FILE* spawn_pty_with_shell(const char* default_shell) {
  //
  return NULL;
}

int main(void) {
  //
  char* default_shell = getenv("SHELL");
  if (!default_shell) { // don't know if this can fail
    default_shell = "/usr/bin/bash";
  }
  printf("%s\n", default_shell);
  FILE* stdout_fd = spawn_pty_with_shell(default_shell);
  if (!stdout_fd) {
    fprintf(stderr, "could not spawn pty with shell\n");
    exit(1);
  }
  Buffer* read_buf = containers_buffer_create(128);
  while (true) {
    Buffer* file_buffer = read_from_fd(stdout_fd);
  }
}
