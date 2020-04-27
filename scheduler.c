#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/wait.h>

#define UNIT_TIME() { for (volatile unsigned long i = 0 ; i < 1000000UL ; i++); }
#define GET_TIME 333

typedef struct {
    char name[32];
    int t_re, t_ex;
    pid_t pid;
} process;

int execute_process(process pro){
	pid_t pid = fork();

	if (pid < 0) {
		perror("failed to fork");
		return -1;
	}

	if (pid == 0) {
		struct timespec t_start, t_end;
		char to_dmesg[200];
		syscall(GET_TIME, &t_start);
		for (int i = 0; i < pro.t_ex; i++) {
			UNIT_TIME();
		}
		syscall(GET_TIME, &t_end);
		sprintf(to_dmesg, "[project1] %d %ld.%09ld %ld.%09ld\n", getpid(), t_start.tv_sec, t_start.tv_nsec, t_end.tv_sec, t_end.tv_nsec);
		syscall(PRINTK, to_dmesg);
		exit(0);
	}
	
	/* Assign child to another core prevent from interupted by parant */
	//proc_assign_cpu(pid, CHILD_CPU);

	return pid;
}

void FIFO(process* pros, int process_num){
    
    int RT = 1e9;
    int p_to_run;
    for(int i = 0 ; i < process_num ; i++){
        if(pros[i].pid == -1)   continue;
        if(pros[i].t_re < RT){
            p_to_run = i;
            RT = pros[i].t_re;
        }
    }

}

void RR(process* pros, int process_num){
    
}

void SJF(process* pros, int process_num){
    
}

void PSJF(process* pros, int process_num){
    
}

int main(){
    char policy[10];
    int process_num;
    scanf("%s\n%d", &policy, &process_num);
    process* pros = (process *) malloc(sizeof(process) * process_num);
    for(int i = 0 ; i < process_num ; i++){
        scanf("%s %d %d", &pros[i].name, &pros[i].t_re, &pros[i].t_ex);
    }
    switch(policy[0]){
        case 'F':
            FIFO(pros, process_num);
            break;
        case 'R':
            RR(pros, process_num);
            break;
        case 'S':
            SJF(pros, process_num);
            break;
        case 'P':
            PSJF(pros, process_num);
            break;
    }
    return 0;
}