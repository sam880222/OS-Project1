#include "child.h"
#include "control.h"

int create_pro(int t_re, int t_ex){
    pid_t pid = fork();

    if (pid < 0) {
		perror("failed to fork");
		return -1;
	}

    /*parent process*/
    if(pid > 0){
        change_cpu(pid, 1);
        return pid;
    }

    /*child process*/
    else
    {
        struct timespec t_start, t_end;
		char msg[200];
		syscall(GET_TIME, &t_start);
		for (int i = 0; i < pro.t_ex; i++) {
			UNIT_TIME();
		}
		syscall(GET_TIME, &t_end);
		sprintf(msg, "[project1] %d %ld.%09ld %ld.%09ld\n", getpid(), t_start.tv_sec, t_start.tv_nsec, t_end.tv_sec, t_end.tv_nsec);
		syscall(PRINTK, msg);
		exit(0);
    }
}
