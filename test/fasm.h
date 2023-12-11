#pragma once

#include <stddef.h>

extern char **fasm_environ;

void fasm__start();
int fasm_main();
size_t fasm_strlen(const char *);
char *fasm_strchr(const char *, int);
int fasm_strcmp(const char *, const char *);
int fasm_strncmp(const char *, const char *, size_t);
char *fasm_getenv(const char *);
char *fasm_memcpy(void *, const void *, size_t);
char *fasm_memset(void *, int, size_t);
int fasm_memcmp(const void *, const void *, size_t);
int fasm_bcmp(const void *, const void *, size_t);
void fasm_bzero(void *, size_t);
int fasm_abs(int);
long fasm_labs(long);
long long fasm_llabs(long long);
int fasm_isascii(int);
int fasm_isdigit(int);
int fasm_isalnum(int);
int fasm_islower(int);
int fasm_isupper(int);
int fasm_isalpha(int);
int fasm_isxdigit(int);
int fasm_tolower(int);
int fasm_toupper(int);
