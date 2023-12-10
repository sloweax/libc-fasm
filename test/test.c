#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define ASSERT(x) (test(#x, __LINE__, __FILE__, (x)))
#define CASSERT(x) ASSERT((x) == (fasm_##x))

extern char **environ;
extern char **fasm_environ;

int fasm_main() { return 0; }
extern size_t fasm_strlen(const char *);
extern char *fasm_strchr(const char *, int);
extern int fasm_strcmp(const char *, const char *);
extern int fasm_strncmp(const char *, const char *, size_t);
extern char *fasm_getenv(const char *);
extern char *fasm_memcpy(void *, const void *, size_t);
extern char *fasm_memset(void *, int, size_t);
extern int fasm_memcmp(const void *, const void *, size_t);
extern int fasm_bcmp(const void *, const void *, size_t);
extern void fasm_bzero(void *, size_t);
extern int fasm_abs(int);
extern long fasm_labs(long);
extern long long fasm_llabs(long long);
extern int fasm_isascii(int);
extern int fasm_isdigit(int);
extern int fasm_isalnum(int);
extern int fasm_islower(int);
extern int fasm_isupper(int);
extern int fasm_isalpha(int);
extern int fasm_isxdigit(int);
extern int fasm_tolower(int);
extern int fasm_toupper(int);

int ret = 0;

int test(char *exp, int line, char *file, int status) {
  if (!status) {
    printf("FAILED\t%s:%d %s\n", file, line, exp);
    ret = 1;
  }

  return status;
}

int main(int argc, char **argv, char **envp) {

  fasm_environ = environ;

  CASSERT(strlen("a"));
  CASSERT(strlen("abc"));
  CASSERT(strlen(""));

  CASSERT(strcmp("abc", "abc"));
  CASSERT(strcmp("abc", "123"));
  CASSERT(strcmp("b", "a"));
  CASSERT(strcmp("a", "b"));
  CASSERT(strcmp("1b", "1a"));
  CASSERT(strcmp("1a", "1b"));
  CASSERT(strcmp("1b", "1"));
  CASSERT(strcmp("1", "1b"));
  CASSERT(strcmp("\x00", "\xff"));
  CASSERT(strcmp("\xff", "\x00"));

  CASSERT(strncmp("abc", "abc", 0));
  CASSERT(strncmp("abc", "123", 0));
  CASSERT(strncmp("abc", "abc", 3));
  CASSERT(strncmp("aaa", "bbb", 3));
  CASSERT(strncmp("bbb", "aaa", 3));
  CASSERT(strncmp("1aaa", "1bbb", 3));
  CASSERT(strncmp("1bbb", "1aaa", 3));
  CASSERT(strncmp("abc123", "abc456", 3));
  CASSERT(strncmp("\x00 def", "\x00 abc", 5));
  CASSERT(strncmp("\x01\x00", "\x01\x00", 5));
  CASSERT(strncmp("\x01\x02\x00", "\x01\x00", 1));
  CASSERT(strncmp("1b", "1", 2));
  CASSERT(strncmp("1", "1b", 2));
  CASSERT(strncmp("\x00", "\xff", 1));
  CASSERT(strncmp("\xff", "\x00", 1));

  char *tmpstr = "1234567890";
  CASSERT(strchr(tmpstr, '1'));
  CASSERT(strchr(tmpstr, '2'));
  CASSERT(strchr(tmpstr, '0'));
  CASSERT(strchr(tmpstr, 'a'));

  CASSERT(getenv("TEST_ENV"));
  CASSERT(getenv("TEST_EMPTY"));
  CASSERT(getenv("TEST_EQ"));

  char buf[65];
  char bufones[sizeof(buf)];

  for (size_t i = 0; i < sizeof(buf); i++) {
    bufones[i] = 1;
    buf[i] = 0;
  }

  bufones[sizeof(buf) - 1] = 0;

  CASSERT(memcpy(buf, bufones, 0));

  for (size_t i = 0; i <= 32; i++) {
    memcpy(buf, bufones, i);
    CASSERT(strlen(bufones));
    CASSERT(strlen(buf) == i);
  }

  fasm_memcpy(buf, bufones, sizeof(buf) - 1);
  CASSERT(strlen(bufones));
  CASSERT(strlen(buf));

  CASSERT(memset(buf, 0, sizeof(buf)));
  CASSERT(strlen(buf));

  int tmpint = 1;
  for (size_t i = 0; i < sizeof(buf); i++) {
    fasm_memset(buf, tmpint, i);
    if (!CASSERT(strlen(buf)))
      break;
    for (size_t j = 0; j < i; j++) {
      if (!ASSERT(buf[j] == tmpint))
        goto out;
    }
    tmpint++;
    fasm_memset(buf, 0, i);
  }
out:

  CASSERT(memcmp("abc", "abc", 0));
  CASSERT(memcmp("abc", "123", 0));
  CASSERT(memcmp("abc", "abc", 3));
  CASSERT(memcmp("aaa", "bbb", 3));
  CASSERT(memcmp("bbb", "aaa", 3));
  CASSERT(memcmp("1aaa", "1bbb", 3));
  CASSERT(memcmp("1bbb", "1aaa", 3));
  CASSERT(memcmp("abc123", "abc456", 3));
  CASSERT(memcmp("abcd\x00", "abcd\xff", 5));
  CASSERT(memcmp("abcd\xff", "abcd\x00", 5));

  CASSERT(bcmp("abcx", "abcz", 0));
  CASSERT(bcmp("abcx", "123z", 0));
  CASSERT(bcmp("abcx", "abcz", 3));
  CASSERT(bcmp("aaa", "bbb", 3));
  CASSERT(bcmp("bbb", "aaa", 3));
  CASSERT(bcmp("1aaa", "1bbb", 3));
  CASSERT(bcmp("1bbb", "1aaa", 3));
  CASSERT(bcmp("abc123", "abc456", 3));
  CASSERT(bcmp("abcd\x00", "abcd\xff", 5));
  CASSERT(bcmp("abcd\xff", "abcd\x00", 5));

  fasm_memset(buf, 1, sizeof(buf));
  fasm_bzero(buf, sizeof(buf));

  for (size_t i = 0; i < sizeof(buf); i++) {
    if (!ASSERT(buf[i] == 0))
      break;
  }

  CASSERT(abs(INT_MAX));
  CASSERT(abs(INT_MIN + 1));

  CASSERT(labs(LONG_MAX));
  CASSERT(labs(LONG_MIN + 1));

  CASSERT(llabs(LLONG_MAX));
  CASSERT(llabs(LLONG_MIN + 1));

  ASSERT(fasm_isdigit('0'));
  ASSERT(fasm_isdigit('9'));
  ASSERT(!fasm_isdigit('9' + 1));
  ASSERT(!fasm_isdigit('0' - 1));

  ASSERT(fasm_islower('a'));
  ASSERT(fasm_islower('z'));
  ASSERT(!fasm_islower('z' + 1));
  ASSERT(!fasm_islower('a' - 1));

  ASSERT(fasm_isupper('A'));
  ASSERT(fasm_isupper('Z'));
  ASSERT(!fasm_isupper('Z' + 1));
  ASSERT(!fasm_isupper('A' - 1));

  ASSERT(fasm_isalpha('A'));
  ASSERT(fasm_isalpha('Z'));
  ASSERT(!fasm_isalpha('Z' + 1));
  ASSERT(!fasm_isalpha('A' - 1));
  ASSERT(fasm_isalpha('a'));
  ASSERT(fasm_isalpha('z'));
  ASSERT(!fasm_isalpha('z' + 1));
  ASSERT(!fasm_isalpha('a' - 1));

  ASSERT(fasm_isalnum('A'));
  ASSERT(fasm_isalnum('Z'));
  ASSERT(!fasm_isalnum('Z' + 1));
  ASSERT(!fasm_isalnum('A' - 1));
  ASSERT(fasm_isalnum('a'));
  ASSERT(fasm_isalnum('z'));
  ASSERT(!fasm_isalnum('z' + 1));
  ASSERT(!fasm_isalnum('a' - 1));
  ASSERT(fasm_isalnum('0'));
  ASSERT(fasm_isalnum('9'));
  ASSERT(!fasm_isalnum('0' - 1));
  ASSERT(!fasm_isalnum('9' + 1));

  ASSERT(fasm_isascii(0));
  ASSERT(fasm_isascii(1));
  ASSERT(fasm_isascii(127));
  ASSERT(!fasm_isascii(128));
  ASSERT(!fasm_isascii(-1));

  ASSERT(fasm_isxdigit('f'));
  ASSERT(!fasm_isxdigit('f' + 1));
  ASSERT(fasm_isxdigit('F'));
  ASSERT(!fasm_isxdigit('F' + 1));
  ASSERT(fasm_isxdigit('a'));
  ASSERT(!fasm_isxdigit('a' - 1));
  ASSERT(fasm_isxdigit('A'));
  ASSERT(!fasm_isxdigit('A' - 1));
  ASSERT(fasm_isxdigit('0'));
  ASSERT(!fasm_isxdigit('0' - 1));
  ASSERT(fasm_isxdigit('9'));
  ASSERT(!fasm_isxdigit('9' + 1));

  CASSERT(tolower('A'));
  CASSERT(tolower('Z'));
  CASSERT(tolower('A' - 1));
  CASSERT(tolower('Z' + 1));

  CASSERT(toupper('a'));
  CASSERT(toupper('z'));
  CASSERT(toupper('a' - 1));
  CASSERT(toupper('z' + 1));

  return ret;
}
