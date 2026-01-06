#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "directories.h"

// typedef struct
// {
//     char name[256];
//     off_t size;
//     mode_t mode;
//     time_t mtime;
//     uid_t uid;
//     gid_t gid;
// } detailed_file_info_t;

int get_detailed_info(const char *path, detailed_file_info_t *info){
    struct stat st;

    if (stat(path, &st) == -1){
        perror("stat");
        return -1;
    };

    strncpy(info->name, path, sizeof(info->name) - 1);
    info->name[sizeof(info->name) - 1] = '\0';

    info->size = st.st_size;
    info->mode = st.st_mode;
    info->mtime = st.st_mtime;
    info->uid = st.st_uid;
    info->gid = st.st_gid;

    return 0;
}

void print_permissions(mode_t mode) {
    printf(S_ISDIR(mode) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w": "-");
    printf((mode & S_IXUSR) ? "x": "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w": "-");
    printf((mode & S_IXGRP) ? "x": "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w": "-");
    printf((mode & S_IXOTH) ? "x": "-");

}

void print_detailed_file_info(const detailed_file_info_t *info ){
    // print permissions
    print_permissions(info->mode);

    // print owner & group
    struct passwd *pw = getpwuid(info->uid);
    struct group *gr = getgrgid(info->gid);

    printf(" %8s %8s", pw ? pw->pw_name : "Unknown", gr ? gr->gr_name : "Unknown");

    // print size
    printf(" %8ld", info->size);

    // print time
    char time_str[64];
    struct tm *tm_info = localtime(&info->mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M",tm_info);
    printf(" %s", time_str);

    printf(" %s", info->name);

    // print type indicator
    if (S_ISDIR(info->mode)) {
        printf("/");
    }  else if (info->mode & S_IXUSR) {
        printf("*");
    }

    printf("\n");

}

int list_directory_detailed(const char *directory_path){
    DIR *dir = opendir(directory_path);

    if (dir == NULL){
        perror("opendir");
        return -1;
    }

    printf("\nDetailed listing of %s:\n", directory_path);
    printf("Permissions  Owner   Group       Size Time       Name\n");
    printf("--------------------------------------------------------\n");

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL){

        if ((strcmp(entry->d_name, ".")) == 0 || (strcmp(entry->d_name, "..")) == 0){
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", directory_path, entry->d_name);

        detailed_file_info_t info;
        if(get_detailed_info(full_path, &info) == 0){
            strcpy(info.name, entry->d_name);

            print_detailed_file_info(&info);
        }
    }

    closedir(dir);
    return 0;    
}