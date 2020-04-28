#define _GNU_SOURCE
#include <sys/types.h>
#include <stdbool.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/wait.h>

#ifndef CONTROL
#define CONTROL

#define UNIT_TIME() { for (volatile unsigned long i = 0 ; i < 1000000UL ; i++); }
#define GETTIME 333
#define PRINTK 334

typedef struct {
    char name[32];
    int t_re, t_ex;
    pid_t pid;
    struct timespec t_start;
} process;

typedef struct {
    int q[30];
    int len;
} priority_q;

typedef struct {
    int q[30];
    int len;
    int head, tail;
} queue;

void change_cpu(pid_t pid, int core);
void increase_priority(pid_t pid);
void decrease_priority(pid_t pid);
int create_pro(process pro);
int pq_pop(priority_q* pq, int* values);
void pq_append(priority_q* pq, int n, int* values);
int q_pop(queue* q);
void q_append(queue* q, int n);

#endif
