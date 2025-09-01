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

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (file_size < 0){
        fclose(fp);
        return FILE_ERROR_NOT_FOUND;
    }

    *content = malloc(file_size + 1);
    if (content == NULL){
        fclose(fp);
        return FILE_ERROR_MEMORY;
    }

    size_t bytes_read = fread(*content, 1, file_size, fp);
    (*content)[bytes_read] = '\0';

    *size = bytes_read;
    fclose(fp);
    return FILE_SUCCESS;
}