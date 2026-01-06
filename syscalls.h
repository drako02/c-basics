#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <sys/types.h>

int sys_open_file(const char* pathname, int flags);
ssize_t sys_read_file(int fd, void* buffer, size_t count);
ssize_t sys_write_file(int fd, const void* buffer, size_t count);
int sys_close_file(int fd);

int sys_list_directory(const char* path);

#endif