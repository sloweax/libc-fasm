#include "../include/fcntl.h"
#include "../include/stdint.h"
#include "../include/stdlib.h"
#include "../include/string.h"
#include "../include/unistd.h"

#define STR(x) STR_HELPER(x)
#define STR_HELPER(x) #x
#define ASSERT(x) (test(#x, STR(__LINE__), __FILE__, (x)))

int ret = 0;

int test(char *exp, char *line, char *file, int status) {
  if (!status) {
    write(1, "FAILED\t", 7);
    write(1, file, strlen(file));
    write(1, ":", 1);
    write(1, line, strlen(line));
    write(1, " ", 1);
    write(1, exp, strlen(exp));
    write(1, "\n", 1);
    ret = 1;
  }

  return status;
}

int main(int argc, char **argv, char **envp) {

  ASSERT(strlen("a") == 1);
  ASSERT(strlen("abc") == 3);
  ASSERT(strlen("") == 0);

  ASSERT(strcmp("abc", "abc") == 0);
  ASSERT(strcmp("abc", "123") != 0);
  ASSERT(strcmp("b", "a") > 0);
  ASSERT(strcmp("a", "b") < 0);
  ASSERT(strcmp("1b", "1a") > 0);
  ASSERT(strcmp("1a", "1b") < 0);

  ASSERT(strncmp("abc", "abc", 0) == 0);
  ASSERT(strncmp("abc", "123", 0) == 0);
  ASSERT(strncmp("abc", "abc", 3) == 0);
  ASSERT(strncmp("aaa", "bbb", 3) < 0);
  ASSERT(strncmp("bbb", "aaa", 3) > 0);
  ASSERT(strncmp("abc123", "abc456", 3) == 0);
  ASSERT(strncmp("\x00 def", "\x00 abc", 5) == 0);

  char *tmpstr = "1234567890";
  ASSERT(strchr(tmpstr, '1') == tmpstr);
  ASSERT(strchr(tmpstr, '2') == tmpstr + 1);
  ASSERT(strchr(tmpstr, '0') == tmpstr + 9);
  ASSERT(strchr(tmpstr, 'a') == NULL);

  ASSERT(strcmp(getenv("TEST_ENV"), "123") == 0);
  ASSERT(strcmp(getenv("TEST_EMPTY"), "") == 0);
  ASSERT(strcmp(getenv("TEST_EQ"), "=") == 0);
  ASSERT(getenv("TEST_NONEXISTANT") == NULL);

  char buf[65];
  char bufones[sizeof(buf)];

  for (size_t i = 0; i < sizeof(buf); i++) {
    bufones[i] = 1;
    buf[i] = 0;
  }

  bufones[sizeof(buf) - 1] = 0;

  for (size_t i = 0; i <= 32; i++) {
    memcpy(buf, bufones, i);
    ASSERT(strlen(bufones) == sizeof(buf) - 1);
    ASSERT(strlen(buf) == i);
  }

  memcpy(buf, bufones, sizeof(buf) - 1);
  ASSERT(strlen(bufones) == sizeof(buf) - 1);
  ASSERT(strlen(buf) == sizeof(buf) - 1);

  memset(buf, 0, sizeof(buf));
  ASSERT(strlen(buf) == 0);

  int tmpint = 1;
  for (size_t i = 0; i < sizeof(buf); i++) {
    memset(buf, tmpint++, i);
    if (!ASSERT(strlen(buf) == i))
      break;
    memset(buf, 0, i);
  }

  return ret;
}
