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

int create_pro(process pro){
    pid_t pid = fork();

    if (pid < 0) {        
		perror("failed to fork");
		return -1;
	}

    /*parent process*/
    if(pid > 0){
        decrease_priority(pid);
        printf("%s %d\n", pro.name, pid);
        change_cpu(pid, 1);
        return pid;
    }

    /*child process*/
    else
    {        
        struct timespec t_start, t_end;
		char msg[200];
		syscall(GETTIME, &t_start);
		for (int i = 0; i < pro.t_ex; i++) {
			UNIT_TIME();
		}
		syscall(GETTIME, &t_end);
		sprintf(msg, "%d %ld.%09ld %ld.%09ld\n", getpid(), t_start.tv_sec, t_start.tv_nsec, t_end.tv_sec, t_end.tv_nsec);
		syscall(PRINTK, msg);
        // printf("%s done!", pro.name);
		exit(0);
    }
}