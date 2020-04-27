#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"

void RR(process* pros, int process_num){
    return;      
}

void SJF(process* pros, int process_num){
    return;    
}

void PSJF(process* pros, int process_num){
    return;   
}

int main(){
    char policy[10];
    int process_num;
    scanf("%s\n%d", &policy, &process_num);
    process* pros = (process *) malloc(sizeof(process) * process_num);
    for(int i = 0 ; i < process_num ; i++){
        scanf("%s %d %d", &pros[i].name, &pros[i].t_re, &pros[i].t_ex);
        pros[i].pid = -1;
    }

    change_cpu(getpid(), 0);

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