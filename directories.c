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
