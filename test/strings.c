#include "strings.h"
#include "unit.h"
#include <strings.h>

void test_strings() {
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
}
