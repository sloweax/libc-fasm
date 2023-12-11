#include <stdio.h>

int test(char *exp, int line, char *file, int status) {
  if (!status) {
    printf("FAILED\t%s:%d %s\n", file, line, exp);
  }

  return status;
}
