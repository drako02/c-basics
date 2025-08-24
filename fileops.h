#ifndef FILEOPS_H
#define  FILEOPS_H

#include <stdio.h>

#define FILE_SUCCESS 0
#define FILE_ERROR_NOT_FOUND -1
#define FILE_ERROR_PERMISSION -2
#define FILE_ERROR_MEMORY -3

typedef struct {
    char name[256];
    long size;
    int is_directory;
} file_info_t;

int read_file_content(const char *filename, char **content, size_t *size);
int write_file_content(const char *filename, const char *content);
int file_exists(const char *filename);
void print_file_info(const file_info_t *info);

#endif