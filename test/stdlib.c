#include "fasm.h"
#include "stdlib.h"
#include "unit.h"
#include <limits.h>
#include <stdlib.h>

void test_stdlib() {

  CASSERT(getenv("TEST_ENV"));
  CASSERT(getenv("TEST_EMPTY"));
  CASSERT(getenv("TEST_EQ"));

  CASSERT(abs(INT_MAX));
  CASSERT(abs(INT_MIN + 1));

  CASSERT(labs(LONG_MAX));
  CASSERT(labs(LONG_MIN + 1));

  CASSERT(llabs(LLONG_MAX));
  CASSERT(llabs(LLONG_MIN + 1));
}
