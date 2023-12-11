#include "ctype.h"
#include "fasm.h"
#include "stdlib.h"
#include "string.h"
#include "strings.h"
#include "unistd.h"
#include "unit.h"

extern char **environ;

int main(int argc, char **argv, char **envp) {

  fasm_environ = environ;

  test_string();
  test_strings();
  test_ctype();
  test_stdlib();
  test_unistd();

  return test_status;
}
