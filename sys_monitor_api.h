#ifndef SYS_MONITOR_SYS_MONITOR_API_H
#define SYS_MONITOR_SYS_MONITOR_API_H

#ifdef __cplusplus
extern "C" {
#endif

/* Returns number of cores on the current hardware */
long get_core_num();

/* Gets the core's temperature given index i;
   if core with such index does not exist - returns 0 */
double get_core_temp_by_idx(int i);

#ifdef __cplusplus
}
#endif

#endif //SYS_MONITOR_SYS_MONITOR_API_H
