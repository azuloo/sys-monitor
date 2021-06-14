#ifndef SYS_MONITOR_SYS_MONITOR_INTERNALS_H
#define SYS_MONITOR_SYS_MONITOR_INTERNALS_H

#include <stdlib.h>

double get_core_temp(int i);

static void get_core_device_dir(char *buf);
static char *get_system_dif_buf(struct dirent *sys_dir_ent);
static char *get_system_name_file(const char *sys_dir_buf);
static double get_core_temp_by_path(const char *path);

#endif //SYS_MONITOR_SYS_MONITOR_INTERNALS_H
