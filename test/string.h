#pragma once

#include <stddef.h>

size_t fasm_strlen(const char *);
char *fasm_strchr(const char *, int);
int fasm_strcmp(const char *, const char *);
int fasm_strncmp(const char *, const char *, size_t);
char *fasm_memcpy(void *, const void *, size_t);
char *fasm_memset(void *, int, size_t);
int fasm_memcmp(const void *, const void *, size_t);

void test_string();
