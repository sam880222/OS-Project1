#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_my_printk(char* msg) {    
    printk(KERN_INFO "[Project1] %s\n", msg);
    return;
}