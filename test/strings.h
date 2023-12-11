#pragma once

#include <stddef.h>

int fasm_bcmp(const void *, const void *, size_t);
void fasm_bzero(void *, size_t);

void test_strings();
