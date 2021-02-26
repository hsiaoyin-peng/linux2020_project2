#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/sched.h>

//static wait_queue_entry_t wait;
static bool condition1 = false;
static bool condition2 = false;
static bool condition3 = false;
static DECLARE_WAIT_QUEUE_HEAD(project2_queue_1);
static DECLARE_WAIT_QUEUE_HEAD(project2_queue_2);
static DECLARE_WAIT_QUEUE_HEAD(project2_queue_3);

asmlinkage int sys_enter_wait_queue(int x)
{
    switch(x){
        case 1:
            condition1 = false;
            wait_event(project2_queue_1, condition1 == true);
            break;
        case 2:
            condition2 = false;
            wait_event(project2_queue_2, condition2 == true);
            break;
        case 3:
            condition3 = false;
            wait_event(project2_queue_3, condition3 == true);
            break;
        default:
            break;
    }

    return 0;
}

asmlinkage int sys_clean_wait_queue(int x)
{
    switch(x){
        case 1:
            condition1 = true;
            wake_up(&project2_queue_1);
            break;
        case 2:
            condition2 = true;
            wake_up(&project2_queue_2);
            break;
        case 3:
            condition3 = true;
            wake_up(&project2_queue_3);
            break;
        default:
            break;
    }
    return 0;
}
