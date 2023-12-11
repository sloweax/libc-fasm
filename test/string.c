#include "string.h"
#include "unit.h"
#include <string.h>

void test_string() {
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

  char buf[65];
  char bufones[sizeof(buf)];

  memset(bufones, 1, sizeof(bufones));
  memset(buf, 0, sizeof(buf));

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

  return;
}
