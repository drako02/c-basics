#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *program_name)
{
    printf("Usage: %s [directory]\n", program_name);
    printf(" Lists files in the specified directory\n");
    printf(" If no directly given, uses current directory\n");
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

    printf("Exploring directory: %s\n", directory);  // TODO Actual implementation
    return 0;
}
