#include "control.h"

void change_cpu(pid_t pid, int core){
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
    sched_setaffinity(pid, sizeof(mask), &mask);

	return;
}

void increase_priority(pid_t pid){
    struct sched_param p;
    /* SCHED_IDLE should set priority to 0 */
	p.sched_priority = 99;

	sched_setscheduler(pid, SCHED_FIFO, &p);
    return;
}

void decrease_priority(pid_t pid){
    struct sched_param p;
    /* SCHED_IDLE should set priority to 0 */
	p.sched_priority = 1;

	sched_setscheduler(pid, SCHED_FIFO, &p);
    return;
}