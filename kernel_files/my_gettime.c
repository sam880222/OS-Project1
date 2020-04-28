#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage void sys_my_gettime(struct timespec *t) {    
    getnstimeofday(t);    
    return ;
}
