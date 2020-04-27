#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "control.h"

int create_pro(int t_re, int t_ex);