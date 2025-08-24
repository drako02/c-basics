#include "fileops.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int read_file_content(const char *filename, char **content, size_t *size)
{
    if (filename == NULL || content == NULL || size == NULL)
    {
        return FILE_ERROR_MEMORY;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        if (errno == ENOENT){
            return FILE_ERROR_NOT_FOUND;
        } else if (errno == EACCES){
            return FILE_ERROR_PERMISSION;
        }
        
        return FILE_ERROR_NOT_FOUND;
    }
}