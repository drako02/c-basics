#include "syscalls.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int sys_open_file(const char* pathname, int flags) {
    int fd = open(pathname, flags);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("Opened file descriptor:%d\n", fd);
    return fd;
}

ssize_t sys_read_file(int fd, void* buffer, size_t count) {
    ssize_t bytes_read = read(fd, buffer, count);
    if (bytes_read == -1) {
        perror("read");
        return -1;
    }

    printf("Read %zd bytes from fd %d\n", bytes_read, fd);
    return bytes_read;
}

ssize_t sys_write_file(int fd, const void* buffer, size_t count) {
    ssize_t bytes_written = write(fd, buffer, count);
    if (bytes_written == -1) {
        perror("write");
        return -1;
    }
    printf("Wrote %zd bytes to fd %d\n", bytes_written, fd);
    return bytes_written;
}

int sys_close_file(int fd) {
    if (close(fd) == -1) {
        perror("error");
        return -1;
    }
    printf("Closed file descriptor: %d\n", fd);
    return 0;
}

int sys_list_directory(const char* path) {
    printf("Listing directory: %s\n", path);

    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return -1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}