#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

typedef struct
{
    char name[256];
    off_t size;
    mode_t mode;
    time_t mtime;
    uid_t uid;
    gid_t gid;
} detailed_file_info_t;

int get_detailed_info(const char *path, detailed_file_info_t *info);
void print_permissions(mode_t mode);
void print_detailed_file_info(const detailed_file_info_t *info);
int list_directory_detailed(const char *directory_path);

#endif