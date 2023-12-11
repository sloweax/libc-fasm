#include "ctype.h"
#include "unit.h"
#include <ctype.h>
#include <stdio.h>

void test_ctype() {
  int r;
  for (int i = -0xff; i <= 0xff; i++) {
    r = CASSERT(isdigit(i) ? 1 : 0) && CASSERT(islower(i) ? 1 : 0) &&
        CASSERT(isupper(i) ? 1 : 0) && CASSERT(isalpha(i) ? 1 : 0) &&
        CASSERT(isalnum(i) ? 1 : 0) && CASSERT(isascii(i) ? 1 : 0) &&
        CASSERT(isxdigit(i) ? 1 : 0) && CASSERT(tolower((unsigned char)i)) &&
        CASSERT(toupper((unsigned char)i));
    if (!r) {
      printf("failed on i = %d\n", i);
      break;
    }
  }
}
