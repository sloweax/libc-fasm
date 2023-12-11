#pragma once

#define ASSERT(x) (test(#x, __LINE__, __FILE__, (x)))
#define CASSERT(x) ASSERT((x) == (fasm_##x))

extern int test_status;

int test(char *exp, int line, char *file, int status);
