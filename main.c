#define _XOPEN_SOURCE 600

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

struct PTY {
  int master, slave;
};

bool pt_pair(struct PTY* pty) {
  char* slave_name;

  /* Opens the PTY master device. This is the file descriptor that
   * we're reading from and writing to in our terminal emulator.
   *
   * We're going for BSD-style management of the controlling terminal:
   * Don't try to change anything now (O_NOCTTY), we'll issue an
   * ioctl() later on. */
  pty->master = posix_openpt(O_RDWR | O_NOCTTY);
  if (pty->master == -1) {
    perror("posix_openpt");
    return false;
  }

  /* grantpt() and unlockpt() are housekeeping functions that have to
   * be called before we can open the slave FD. Refer to the manpages
   * on what they do. */
  if (grantpt(pty->master) == -1) {
    perror("grantpt");
    return false;
  }

  if (unlockpt(pty->master) == -1) {
    perror("grantpt");
    return false;
  }

  /* Up until now, we only have the master FD. We also need a file
   * descriptor for our child process. We get it by asking for the
   * actual path in /dev/pts which we then open using a regular
   * open(). So, unlike pipe(), you don't get two corresponding file
   * descriptors in one go. */

  slave_name = ptsname(pty->master);
  if (slave_name == NULL) {
    perror("ptsname");
    return false;
  }

  pty->slave = open(slave_name, O_RDWR | O_NOCTTY);
  if (pty->slave == -1) {
    perror("open(slave_name)");
    return false;
  }

  return true;
}

bool spawn(struct PTY* pty) {
  pid_t p;
  char* env[] = {"TERM=dumb", NULL};

  p = fork();
  if (p == 0) {
    close(pty->master);

    /* Create a new session and make our terminal this process'
     * controlling terminal. The shell that we'll spawn in a second
     * will inherit the status of session leader. */
    setsid();
    if (ioctl(pty->slave, TIOCSCTTY, NULL) == -1) {
      perror("ioctl(TIOCSCTTY)");
      return false;
    }

    dup2(pty->slave, 0);
    dup2(pty->slave, 1);
    dup2(pty->slave, 2);
    close(pty->slave);

    execle(SHELL, "-" SHELL, (char*)NULL, env);
    return false;
  } else if (p > 0) {
    close(pty->slave);
    return true;
  }

  perror("fork");
  return false;
}

int main() {
  //
  int dom_fd = posix_openpt(O_RDWR);
  char* sub_path_name = ptsname(dom_fd);
  grantpt(dom_fd);
  unlockpt(dom_fd);
  printf("%d, %s\n", dom_fd, sub_path_name);
}
