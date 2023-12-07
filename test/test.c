#include "../include/fcntl.h"
#include "../include/stdint.h"
#include "../include/stdlib.h"
#include "../include/string.h"
#include "../include/unistd.h"

#define STR(x) STR_HELPER(x)
#define STR_HELPER(x) #x
#define ASSERT(x) test(#x, STR(__LINE__), __FILE__, (x) == 0)

int ret = 0;

void test(char *exp, char *line, char *file, int status) {
  if (status != 0) {
    write(1, "FAILED\t", 7);
    write(1, file, strlen(file));
    write(1, ":", 1);
    write(1, line, strlen(line));
    write(1, " ", 1);
    write(1, exp, strlen(exp));
    write(1, "\n", 1);
    ret = 1;
  }
}

int main(int argc, char **argv, char **envp) {

  ASSERT(strlen("a") == 1);
  ASSERT(strlen("abc") == 3);
  ASSERT(strlen("") == 0);

  ASSERT(strcmp("abc", "abc") == 0);
  ASSERT(strcmp("abc", "123") != 0);
  ASSERT(strcmp("b", "a") > 0);
  ASSERT(strcmp("a", "b") < 0);

  ASSERT(strncmp("abc", "abc", 0) == 0);
  ASSERT(strncmp("abc", "123", 0) == 0);
  ASSERT(strncmp("abc", "abc", 3) == 0);
  ASSERT(strncmp("aaa", "bbb", 3) < 0);
  ASSERT(strncmp("bbb", "aaa", 3) > 0);
  ASSERT(strncmp("abc123", "abc456", 3) == 0);
  ASSERT(strncmp("\x00 def", "\x00 abc", 5) == 0);

  char *tmp = "1234567890";
  ASSERT(strchr(tmp, '1') == tmp);
  ASSERT(strchr(tmp, '2') == tmp + 1);
  ASSERT(strchr(tmp, '0') == tmp + 9);
  ASSERT(strchr(tmp, 'a') == NULL);

  ASSERT(strcmp(getenv("TEST_ENV"), "123") == 0);
  ASSERT(strcmp(getenv("TEST_EMPTY"), "") == 0);
  ASSERT(strcmp(getenv("TEST_EQ"), "=") == 0);
  ASSERT(getenv("TEST_NONEXISTANT") == NULL);

  return ret;
}
