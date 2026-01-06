#include "fileops.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int read_file_content(const char* filename, char** content, size_t* size) {
    if (filename == NULL || content == NULL || size == NULL) {
        return FILE_ERROR_MEMORY;
    }

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        if (errno == ENOENT) {
            return FILE_ERROR_NOT_FOUND;
        } else if (errno == EACCES) {
            return FILE_ERROR_PERMISSION;
        }

        return FILE_ERROR_NOT_FOUND;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (file_size < 0) {
        fclose(fp);
        return FILE_ERROR_NOT_FOUND;
    }

    *content = malloc(file_size + 1);
    if (content == NULL) {
        fclose(fp);
        return FILE_ERROR_MEMORY;
    }

    size_t bytes_read = fread(*content, 1, file_size, fp);
    (*content)[bytes_read] = '\0';

    *size = bytes_read;
    fclose(fp);
    return FILE_SUCCESS;
}

int write_file_content(const char* filename, const char* content) {
    if (filename == NULL || content == NULL) {
        return FILE_ERROR_MEMORY;
    }

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        if (errno == EACCES) {
            return FILE_ERROR_PERMISSION;
        }
        return FILE_ERROR_NOT_FOUND;
    }

    size_t content_len = strlen(content);
    size_t written = fwrite(content, 1, content_len, fp);

    fclose(fp);

    if (written != content_len) {
        return FILE_ERROR_NOT_FOUND;
    }

    return FILE_SUCCESS;
}

int file_exists(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    }

    return 0;
}

void print_file_info(const file_info_t* info) {
    if (info == NULL) {
        return;
    }

    printf("%-30s %10ld bytes %s\n", info->name, info->size,
           info->is_directory ? "[DIR]" : "[FILE]");
}