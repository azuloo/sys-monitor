#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "sys_monitor_internals.h"

#define SYS_CLASS_DIR "/sys/class/hwmon/"
#define CORE_TEMP_NAME "coretemp"
#define CORE_DEVICE_FILE_NAME "name"

#define DEVICE_PATH_MAX 256
#define DEVICE_NAME_MAX 64

#define GET_CORE_DEF_PATH(buf, size, core_def_dir, i, postfix) \
    snprintf(buf, size, "%s%s%s%d%s", core_def_dir, "/", "temp", i, postfix)
#define SYS_MONITOR_PRINT_ERR(buf) perror(buf)
#define RESET_BUF(buf) memset(buf, '\0', strlen(buf))

struct dirent;

// -----------------------------------------------------------
double get_core_temp(int i)
{
    static char temp_path[DEVICE_PATH_MAX];
    static char core_dir_path[DEVICE_PATH_MAX / 2];

    get_core_device_dir(core_dir_path);
    GET_CORE_DEF_PATH(temp_path, sizeof temp_path / sizeof *temp_path, core_dir_path, i, "_input");

    double cpu_temp = get_core_temp_by_path(temp_path);

    return cpu_temp;
}

// -----------------------------------------------------------
static double get_core_temp_by_path(const char *path)
{
    FILE *temp_file;
    long temp_input;
    double core_temp = 0;
    // At most 100 degrees (multiplied by 1000 in target file)
    char file_contents[7];
    char *end;

    if ((temp_file = fopen(path, "r"))) {
        fscanf(temp_file, "%s", &file_contents[0]);
        temp_input = strtol(file_contents, &end, 10);
        core_temp = (double) temp_input / 1000;
        fclose(temp_file);
    }

    return core_temp;
}

// -----------------------------------------------------------
static char *get_system_dif_buf(struct dirent *sys_dir_ent)
{
    static char sys_dir_buf[PATH_MAX];

    RESET_BUF(sys_dir_buf);
    snprintf(sys_dir_buf, sizeof sys_dir_buf, "%s%s", SYS_CLASS_DIR, sys_dir_ent->d_name);

    return &sys_dir_buf[0];
}

// -----------------------------------------------------------
static char *get_system_name_file(const char *sys_dir_buf)
{
    static char sys_name_file_buf[MAXNAMLEN];

    RESET_BUF(sys_name_file_buf);
    snprintf(sys_name_file_buf, sizeof sys_name_file_buf, "%s%s%s", sys_dir_buf, "/", CORE_DEVICE_FILE_NAME);

    return &sys_name_file_buf[0];
}

// -----------------------------------------------------------
static void get_core_device_dir(char *buf)
{
    DIR *srcdir = opendir(SYS_CLASS_DIR);

    char *sys_name_file_buf;
    char *sys_dir_buf;
    struct dirent *sys_dir_ent;

    static char name_file_contents[DEVICE_NAME_MAX];
    RESET_BUF(name_file_contents);

    if (NULL == srcdir) {
#ifdef DEBUG
    SYS_MONITOR_PRINT_ERR("failed to open srcdir");
#endif
        return;
    }

    while ((sys_dir_ent = readdir(srcdir)) != NULL) {
        if (strcmp(sys_dir_ent->d_name, ".") == 0 || strcmp(sys_dir_ent->d_name, "..") == 0)
            continue;

        sys_dir_buf = get_system_dif_buf(sys_dir_ent);
        sys_name_file_buf = get_system_name_file(sys_dir_buf);

        FILE *name_file = fopen(sys_name_file_buf, "r");

        if (name_file == NULL) {
#ifdef DEBUG
    SYS_MONITOR_PRINT_ERR("failed to open sys_name_file_buf");
#endif
            return;
        }

        fscanf(name_file, "%s", name_file_contents);

        // Identifying if it's the right dir by scanning a device's name
        if ((strcmp(name_file_contents, CORE_TEMP_NAME)) == 0) {
            memcpy(buf, sys_dir_buf, strlen(sys_dir_buf)+1);
            break;
        }

        fclose(name_file);
    }

    closedir(srcdir);
}