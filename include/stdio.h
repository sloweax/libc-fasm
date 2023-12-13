#pragma once

#include "stddef.h"

struct FILE;
typedef struct FILE FILE;

extern FILE __stdin;
extern FILE __stdout;
extern FILE __stderr;

#define stdin (&__stdint)
#define stdout (&__stdout)
#define stderr (&__stderr)

FILE *fopen(const char pathname, const char *mode);
int fclose(FILE *stream);
size_t fwrite_unlocked(const void *p, size_t size, size_t n, FILE *stream);
int fflush_unlocked(FILE *stream);
int fputc_unlocked(int c, FILE *stream);
int fputs_unlocked(const char *, FILE *stream);
