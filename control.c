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

int pq_pop(priority_q* pq, int* values){
    if(pq -> len == 0){
        perror("pop empty queue");
        exit(0);
    }
    int ret = (pq -> q)[0];    
    (pq -> q)[0] = (pq -> q)[--(pq -> len)];
    int i = 0;
    int len = pq -> len;

    while(i < len){        
        if(i*2 + 1 < len){
            int root = (pq -> q)[i];
            int left = (pq -> q)[i*2 + 1];
            if(i*2 + 2 < len){
                int right = (pq -> q)[i*2 + 2];
                if(values[root] <= values[left] && values[root] <= values[right]) break;
                else{
                    if(values[left] < values[right]){
                        (pq -> q)[i] = left;
                        (pq -> q)[i*2 + 1] = root;
                        i = i*2 + 1;
                    }
                    else{
                        (pq -> q)[i] = right;
                        (pq -> q)[i*2 + 2] = root;
                        i = i*2 + 2;
                    }                        
                }                    
            }
            else{
                if(values[left] < values[root]){
                        (pq -> q)[i] = left;
                        (pq -> q)[i*2 + 1] = root;
                        i = i*2 + 1;
                }
                else    break;                    
            }                
        }
        else    break;
    }
    return ret;    
}

void pq_append(priority_q* pq, int n, int* values){
    (pq -> q)[(pq -> len)] = n;
    int i = (pq -> len);
    (pq -> len)++;

    while(i > 0){ 
        int root = (pq -> q)[(i - 1) / 2];
        int now = (pq -> q)[i];
        if(values[now] < values[root]){
            (pq -> q)[i] = root;
            (pq -> q)[(i - 1) / 2] = now;
            i = (i - 1) / 2;
        }
        else    break;                    
    }
    return;
}