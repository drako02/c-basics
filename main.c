#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"

void print_usage(const char *program_name)
{
    printf("Usage: %s [directory]\n", program_name);
    printf(" Lists files in the specified directory\n");
    printf(" If no directly given, uses current directory\n");
}

char *create_path(const char *directory, const char *filename)
{
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + 1 + file_len + 1;

    char *path = malloc(total_len);
    if (path == NULL)
    {
        fprintf(stderr, "Error: Memory Allocation failed\n");
        return NULL;
    }

    strcpy(path, directory);
    if (directory[dir_len - 1] != '/')
    {
        strcat(path, "/");
    }

    strcat(path, filename);

    return path;
}

int safe_string_copy(char *dest, const char *src, size_t dest_size){
    if (dest == NULL || src == NULL || dest_size == 0){
        return -1;
    }

    size_t src_len = strlen(src);
    if(src_len >= dest_size){
        return -1;
    }

    strcpy(dest, src);
    return 0;
}

int main(int argc, char *argv[])
{
    const char *directory;

    if (argc > 2)
    {
        fprintf(stderr, "Error: Too many arguments\n");
        print_usage(argv[0]);
        return 1;
    }

    if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
            print_usage(argv[0]);
            return 0;
        }
        directory = argv[1];
    }
    else
    {
        directory = ".";
    }

    char *fullpath = create_path(directory, "test.txt");
    if (fullpath != NULL){
        printf("Example path: %s\n", fullpath);
        free(fullpath);
        fullpath = NULL;
    }

    // printf("Exploring directory: %s\n", directory);
    return 0;
}