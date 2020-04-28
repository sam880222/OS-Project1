#include "RR.h"

// int cmp_FIFO(const void *a, const void *b) {
//     int rt_a = ((process *)a) -> t_re; 
//     int rt_b = ((process *)b) -> t_re; 
// 	return (rt_a - rt_b);
// }

void RR(process* pros, int process_num){
    long long clock = 0;
    increase_priority(getpid());
    queue q;  
    q.len = 0;
    q.head = 0;
    q.tail = 0;  
    // qsort(pros, process_num, sizeof(process), cmp_FIFO);
    bool running = false;
    int pro_running = -1;
    int finish_num = 0; //num of process that finish 
    int alarm_clock = 0; 
    while (finish_num < process_num){
        /* check whether to finish a process */
        if(running && pros[pro_running].t_ex == 0){
            waitpid(pros[pro_running].pid, NULL, 0);
            pros[pro_running].pid = -1;
            running = false;
            finish_num++;
            if(finish_num == process_num)   break;
        }
        /* check whether to preempt*/
        if(running && alarm_clock == 500){
            decrease_priority(pros[pro_running].pid);
            running = false;
            q_append(&q, pro_running);
        }
        /* create new process when it's ready*/
        for(int i = 0 ; i < process_num ; i++){
            if(pros[i].t_re == clock){
                pros[i].pid = create_pro(pros[i]);
                q_append(&q, i);
            }
        }
        /* check whether to choose a new process to run */
        if(!running && finish_num < process_num){
            pro_running = q_pop(&q);
            alarm_clock = 0;
            running = true;
            printf("%s is running; clock = %lld; pid = %d\n", pros[pro_running].name, clock, getpid());
            increase_priority(pros[pro_running].pid);
        }
        UNIT_TIME();
        if(running){
            pros[pro_running].t_ex--;
            alarm_clock++;
        }
        clock++;
    }
    return;
}