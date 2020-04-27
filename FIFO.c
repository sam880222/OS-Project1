#include "FIFO.h"

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

int cmp(const void *a, const void *b) {
    int rt_a = (struct process *)a -> t_re; 
    int rt_b = (struct process *)b -> t_re; 
	return (rt_a - rt_b);
}

void FIFO(process* pros, int process_num){
    long long clock = 0;

    qsort(pros, process_num, sizeof(process), cmp);
    bool running = false;
    int pro_running = -1;
    int finish_num = 0; //num of process that finish 

    while (finish_num < process_num){
        /* check whether to finish a process */
        if(running && pros[pro_running].t_ex == 0){
            waitpid(pros[pro_running].pid, NULL, 0);
            running = false;
            finish_num++;
        }
        /* create new process when it's ready*/
        for(int i = 0 ; i < process_num ; i++){
            if(pros[i].t_re == clock){
                pros[i].pid = create_pro(pros[i].t_re, pros[i].t_ex);
                decrease_priority(pros[i].pid);
            }
        }
        /* check whether to choose a new process to run */
        if(!running && finish_num < process_num){
            for(int i = 0 ; i < process_num ; i++){
                if(pros[i].pid > 0){
                    pro_running = i;
                    running = true;
                    increase_priority(pros[i].pid);
                    break;
                }
            }
        }
        UNIT_TIME();
        if(running){
            pros[pro_running].t_ex--;
        }
        clock++;
    }
    
    
    for(int i = 0 ; i < process_num ; i++){
        if(pros[i].pid == -1)   continue;
        if(pros[i].t_re < RT){
            p_to_run = i;
            RT = pros[i].t_re;
        }
    }

}