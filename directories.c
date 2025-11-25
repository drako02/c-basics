#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

typedef struct
{
    char name[256];
    off_t size;
    mode_t mode;
    time_t mtime;
    uid_t uid;
    gid_t gid;
} detailed_file_info_t;

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
    print_permissions(info->mode);

    struct passwd *pw = getpwuid(info->uid);
    struct group *gr = getgrgid(info->gid);

    printf(" %8s %8s", pw ? pw->pw_name : "Unknown", gr ? gr->gr_name : "Unknown");

    printf("%8ld", info->size);

    char time_str[64];
    struct tm *tm_info = localtime(&info->mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M",tm_info);
    printf("%s", time_str);
}
