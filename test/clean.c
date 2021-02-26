#include<stdio.h>
#include<sysexits.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<stdlib.h>

int main()
{
    int rand_num1, rand_num2, pid;
    char str[300], file_name[11];
    struct timeval t1, t2;
    FILE *fp;

    gettimeofday(&t1, NULL);
    pid = getpid();
    
    sprintf(file_name, "file_%d.txt", pid);
    fp = fopen(file_name, "a");

    while(1)
    {
        gettimeofday(&t2, NULL);
        if((t2.tv_sec - t1.tv_sec) > 300)
            break;
        srand(time(NULL) + pid);
        rand_num1 = (rand() % 3) + 1;
        rand_num2 = (rand() % 60);
        printf("sleep for %d sec\n", rand_num2);
        sleep(rand_num2);

        sprintf(str, "Wake up all processes in wait queue project2_queue_%d at time %ld\n", rand_num1, t2.tv_sec);
        fputs(str, fp);

        syscall(437, rand_num1);
    }
    fputs("Clean wait queue project2_queue_1\n", fp);
    syscall(437, 1);
    fputs("Clean wait queue project2_queue_2\n", fp);
    syscall(437, 2);
    fputs("Clean wait queue project2_queue_3\n", fp);
    syscall(437, 3);

    fclose(fp);
    printf("process %d completes!\n", pid);
}
