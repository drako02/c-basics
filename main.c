#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"
#include "syscalls.h"
#include <fcntl.h>

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

void test_file_operations(){
    printf("\n=== Testing File Operations ===\n");

    const char *test_file = "test_file.txt";
    printf("File '%s' exists: %s\n", test_file, file_exists(test_file) ? "Yes" : "No");

    const char *test_content = "Hello from fsexplorer!\nThis is a test file.\n";
    int result = write_file_content(test_file, test_content);

    if(result == FILE_SUCCESS){
        printf("Successfully wrote test file\n");
    } else {
        printf("Failed to write test file (error code: %d)\n", result);
        return;
    }

    char *content = NULL;
    size_t size = 0;

    result = read_file_content(test_file, &content, &size);

    if(result == FILE_SUCCESS){
        printf("Read %zu bytes from file:\n", size);
        printf("Content: %s", content);
        free(content);
    } else {
        printf("Failed to read test file (error code: %d)\n", result);
    }

    remove(test_file);

}

void compare_file_access_methods(){
    printf("\n=== Comparing file access methods ===\n");

    char *test_file = "syscall_test.txt";
    char *test_content = "Testing system calls vs library calls";

    printf("\n--- Standard Library Method ---\n");
    FILE *fp =  fopen(test_file, "w");
    if (fp){
        fwrite(test_content, strlen(test_content), 1, fp);
        fclose(fp);
        printf("Standard library: File written successfully\n");
    }

    printf("\n--- System Call Method ---\n");
    int fd = sys_open_file(test_file, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd != -1){
        sys_write_file(fd, test_content, strlen(test_content));
        sys_close_file(fd);
        printf("System calls: File written successfully\n");
    }

    printf("\n--- Reading With System Calls ---\n");
    fd = sys_open_file(test_file, O_RDONLY);
    if (fd != -1){
        char buffer[256];
        ssize_t bytes = sys_read_file(fd, buffer, sizeof(buffer) - 1);
        if (bytes > 0){
            buffer[bytes] = '\0';
            printf("Read content: %s\n", buffer);
        }
        sys_close_file(fd);

    }

    remove(test_file);    

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

    test_file_operations();
    compare_file_access_methods();

    // printf("Exploring directory: %s\n", directory);
    return 0;
}