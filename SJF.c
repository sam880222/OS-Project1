#include "SJF.h"

int cmp_SJF(const void *a, const void *b) {
    int rt_a = ((process *)a) -> t_ex; 
    int rt_b = ((process *)b) -> t_ex; 
	return (rt_a - rt_b);
}

void SJF(process* pros, int process_num){
    long long clock = 0;
    increase_priority(getpid());
    qsort(pros, process_num, sizeof(process), cmp_SJF);
    bool running = false;
    int pro_running = -1;
    int finish_num = 0; //num of process that finish 

    while (finish_num < process_num){
        /* check whether to finish a process */
        if(running && pros[pro_running].t_ex == 0){
            waitpid(pros[pro_running].pid, NULL, 0);
            pros[pro_running].pid = -1;
            running = false;
            finish_num++;
            if(finish_num == process_num)   break;
        }
        /* create new process when it's ready*/
        for(int i = 0 ; i < process_num ; i++){
            if(pros[i].t_re == clock){
                pros[i].pid = create_pro(pros[i]);
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
    return;
}