#pragma once

#include "stddef.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define NULL ((void *)0)

ssize_t read(int fd, const void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int execve(const char *pathname, char *const argv[], char *const envp[]);
int execv(const char *pathname, char *const argv[]);
void _exit(int status);
