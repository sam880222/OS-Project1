#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/wait.h>
#include "control.h"

void FIFO(process* pros, int process_num);