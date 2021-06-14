#ifndef linux
#error Library is only linux compatible.
#endif

#include <unistd.h>
#include "sys_monitor_internals.h"

long get_core_num()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

double get_core_temp_by_idx(int i)
{
    double cpu_temp;
    cpu_temp = get_core_temp(i);

    return cpu_temp;
}