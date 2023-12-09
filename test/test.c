#include "../include/ctype.h"
#include "../include/fcntl.h"
#include "../include/limits.h"
#include "../include/stdint.h"
#include "../include/stdlib.h"
#include "../include/string.h"
#include "../include/strings.h"
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
  ASSERT(strcmp("1b", "1") > 0);
  ASSERT(strcmp("1", "1b") < 0);
  ASSERT(strcmp("\x00", "\xff") < 0);
  ASSERT(strcmp("\xff", "\x00") > 0);

  ASSERT(strncmp("abc", "abc", 0) == 0);
  ASSERT(strncmp("abc", "123", 0) == 0);
  ASSERT(strncmp("abc", "abc", 3) == 0);
  ASSERT(strncmp("aaa", "bbb", 3) < 0);
  ASSERT(strncmp("bbb", "aaa", 3) > 0);
  ASSERT(strncmp("1aaa", "1bbb", 3) < 0);
  ASSERT(strncmp("1bbb", "1aaa", 3) > 0);
  ASSERT(strncmp("abc123", "abc456", 3) == 0);
  ASSERT(strncmp("\x00 def", "\x00 abc", 5) == 0);
  ASSERT(strncmp("\x01\x00", "\x01\x00", 5) == 0);
  ASSERT(strncmp("\x01\x02\x00", "\x01\x00", 1) == 0);
  ASSERT(strncmp("1b", "1", 2) > 0);
  ASSERT(strncmp("1", "1b", 2) < 0);
  ASSERT(strncmp("\x00", "\xff", 1) < 0);
  ASSERT(strncmp("\xff", "\x00", 1) > 0);

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

  ASSERT(memcpy(buf, bufones, 0) == buf);

  for (size_t i = 0; i <= 32; i++) {
    memcpy(buf, bufones, i);
    ASSERT(strlen(bufones) == sizeof(buf) - 1);
    ASSERT(strlen(buf) == i);
  }

  memcpy(buf, bufones, sizeof(buf) - 1);
  ASSERT(strlen(bufones) == sizeof(buf) - 1);
  ASSERT(strlen(buf) == sizeof(buf) - 1);

  ASSERT(memset(buf, 0, sizeof(buf)) == buf);
  ASSERT(strlen(buf) == 0);

  int tmpint = 1;
  for (size_t i = 0; i < sizeof(buf); i++) {
    memset(buf, tmpint++, i);
    if (!ASSERT(strlen(buf) == i))
      break;
    memset(buf, 0, i);
  }

  ASSERT(memcmp("abc", "abc", 0) == 0);
  ASSERT(memcmp("abc", "123", 0) == 0);
  ASSERT(memcmp("abc", "abc", 3) == 0);
  ASSERT(memcmp("aaa", "bbb", 3) < 0);
  ASSERT(memcmp("bbb", "aaa", 3) > 0);
  ASSERT(memcmp("1aaa", "1bbb", 3) < 0);
  ASSERT(memcmp("1bbb", "1aaa", 3) > 0);
  ASSERT(memcmp("abc123", "abc456", 3) == 0);
  ASSERT(memcmp("abcd\x00", "abcd\xff", 5) < 0);
  ASSERT(memcmp("abcd\xff", "abcd\x00", 5) > 0);

  ASSERT(bcmp("abcx", "abcz", 0) == 0);
  ASSERT(bcmp("abcx", "123z", 0) == 0);
  ASSERT(bcmp("abcx", "abcz", 3) == 0);
  ASSERT(bcmp("aaa", "bbb", 3) < 0);
  ASSERT(bcmp("bbb", "aaa", 3) > 0);
  ASSERT(bcmp("1aaa", "1bbb", 3) < 0);
  ASSERT(bcmp("1bbb", "1aaa", 3) > 0);
  ASSERT(bcmp("abc123", "abc456", 3) == 0);
  ASSERT(bcmp("abcd\x00", "abcd\xff", 5) < 0);
  ASSERT(bcmp("abcd\xff", "abcd\x00", 5) > 0);

  memset(buf, 1, sizeof(buf));
  bzero(buf, sizeof(buf));

  for (size_t i = 0; i < sizeof(buf); i++) {
    if (!ASSERT(buf[i] == 0))
      break;
  }

  ASSERT(abs(INT_MAX) == INT_MAX);
  ASSERT(abs(INT_MIN + 1) == INT_MAX);

  ASSERT(labs(LONG_MAX) == LONG_MAX);
  ASSERT(labs(LONG_MIN + 1) == LONG_MAX);

  ASSERT(llabs(LLONG_MAX) == LLONG_MAX);
  ASSERT(llabs(LLONG_MIN + 1) == LLONG_MAX);

  ASSERT(isdigit('0'));
  ASSERT(isdigit('9'));
  ASSERT(!isdigit('9' + 1));
  ASSERT(!isdigit('0' - 1));

  ASSERT(islower('a'));
  ASSERT(islower('z'));
  ASSERT(!islower('z' + 1));
  ASSERT(!islower('a' - 1));

  ASSERT(isupper('A'));
  ASSERT(isupper('Z'));
  ASSERT(!isupper('Z' + 1));
  ASSERT(!isupper('A' - 1));

  ASSERT(isalpha('A'));
  ASSERT(isalpha('Z'));
  ASSERT(!isalpha('Z' + 1));
  ASSERT(!isalpha('A' - 1));
  ASSERT(isalpha('a'));
  ASSERT(isalpha('z'));
  ASSERT(!isalpha('z' + 1));
  ASSERT(!isalpha('a' - 1));

  ASSERT(isalnum('A'));
  ASSERT(isalnum('Z'));
  ASSERT(!isalnum('Z' + 1));
  ASSERT(!isalnum('A' - 1));
  ASSERT(isalnum('a'));
  ASSERT(isalnum('z'));
  ASSERT(!isalnum('z' + 1));
  ASSERT(!isalnum('a' - 1));
  ASSERT(isalnum('0'));
  ASSERT(isalnum('9'));
  ASSERT(!isalnum('0' - 1));
  ASSERT(!isalnum('9' + 1));

  ASSERT(isascii(0));
  ASSERT(isascii(1));
  ASSERT(isascii(127));
  ASSERT(!isascii(128));
  ASSERT(!isascii(-1));

  ASSERT(isxdigit('f'));
  ASSERT(!isxdigit('f' + 1));
  ASSERT(isxdigit('F'));
  ASSERT(!isxdigit('F' + 1));
  ASSERT(isxdigit('a'));
  ASSERT(!isxdigit('a' - 1));
  ASSERT(isxdigit('A'));
  ASSERT(!isxdigit('A' - 1));
  ASSERT(isxdigit('0'));
  ASSERT(!isxdigit('0' - 1));
  ASSERT(isxdigit('9'));
  ASSERT(!isxdigit('9' + 1));

  ASSERT(tolower('A') == 'a');
  ASSERT(tolower('Z') == 'z');
  ASSERT(tolower('A' - 1) == 'A' - 1);
  ASSERT(tolower('Z' + 1) == 'Z' + 1);

  ASSERT(toupper('a') == 'A');
  ASSERT(toupper('z') == 'Z');
  ASSERT(toupper('a' - 1) == 'a' - 1);
  ASSERT(toupper('z' + 1) == 'z' + 1);

  return ret;
}
