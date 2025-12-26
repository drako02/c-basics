#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_command(const char *command){
    printf("Executing command: %s\n", command);

    pid_t pid = fork();

    if (pid == -1){
        perror("fork");
        return -1;
    } else if (pid == 0){
        // Child process
        printf("Child process (PID: %s) executing command\n", getpid());

        // Simple command execution - split on spaces
        char *args[64];
        char *command_copy = malloc(sizeof(command) + 1);
        strcpy(command_copy, command);

        int argc = 0;
        char *token = strtok(command_copy, " ");
        while(token != NULL && argc < 63){
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        execvp(args[0], args);
        perror("execvp");
        free(command_copy);
        exit(1);
    } else {
        // Parent process
        printf("Parent process (PID: %d) waiting for child (PID: %d)\n", getpid(), pid);

        int status;
        waitpid(pid, &status, 0);

        if(WIFEXITED(status)){
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
            return WEXITSTATUS(status);

        } else {
            printf("Child process exited abnormally\n");
            return -1;

        }
    }
}

void show_process_info(){
    printf("\n=== Process Information ===\n");
    printf("Current Process ID (PID): %d\n", getpid());
    printf("Parent Process ID (PPID): %d\n", getppid());
    printf("Process Group ID (PGID): %d\n", getpgrp());
    printf("Session ID (SID): %d\n", getsid(0));

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        printf("Current Working Directory: %s\n, cwd");
    }
}