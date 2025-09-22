#include "syscalls.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


int sys_open_file(const char *pathname, int flags){
    int fd = open(pathname, flags);
    if ( fd == -1) {
        perror("open");
        return -1;
    }

    printf("Opened file descriptor:%d\n", fd);
    return fd;

}

ssize_t sys_read_file(int fd, void *buffer, size_t count){
    ssize_t bytes_read = read(fd, buffer, count);
    if (bytes_read == -1){
        perror("read");
        return -1;
    }

    printf("Read %zd bytes from fd %d\n", bytes_read, fd);
    return bytes_read;
}

ssize_t sys_write_file(int fd, const void *buffer, size_t count){
    ssize_t bytes_written = write(fd, buffer, count);
    if (bytes_written == -1){
        perror("write");
        return -1;
    }
    printf("Wrote %zd bytes to fd %d\n",bytes_written, fd);
    return bytes_written;
}

int sys_close_file(int fd){
    if(close(fd) == -1){
        perror("error");
        return -1;
    }
    printf("Closed file descriptor: %d\n", fd);
    return 0;
}


int sys_list_directory(const char *path){
    // TODO We will use readdir systemcall, but need to include dirent.h
    printf("Listing directory: %s (basic version)\n", path);

    // For now we only test that we can open the directory
    int fd = sys_open_file(path, O_RDONLY);
    if (fd == -1){
        perror("open directory");
        return -1;
    }

    printf("Successfully opened directory fd:%d\n", fd);
    sys_close_file(fd);
    return 0;
}