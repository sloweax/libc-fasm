#include <stdio.h>

int test_status;

int test(char *exp, int line, char *file, int status) {
  if (!status) {
    printf("FAILED\t%s:%d %s\n", file, line, exp);
    test_status = 1;
  }

  return status;
}
