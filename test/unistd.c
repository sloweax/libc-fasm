#include "unistd.h"
#include "unit.h"
#include <unistd.h>

void test_unistd() {
  CASSERT(getpid());
  CASSERT(getppid());
}
