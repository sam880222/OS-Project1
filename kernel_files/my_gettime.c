#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage char* sys_my_gettime(void) {
    struct timespec t;
    getnstimeofday(&t);
    char ret_time[30];
    sprintf(ret_time, "%ld.%09ld", t.tv_sec, t.tv_nsec);
    return ret_time;
}