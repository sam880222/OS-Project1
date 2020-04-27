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

#define UNIT_TIME() { for (volatile unsigned long i = 0 ; i < 1000000UL ; i++); }
#define GET_TIME 333
#define PRINTK 334

typedef struct {
    char name[32];
    int t_re, t_ex;
    pid_t pid;
} process;

void change_cpu(pid_t pid, int core);
void increase_priority(pid_t pid);
void decrease_priority(pid_t pid);
