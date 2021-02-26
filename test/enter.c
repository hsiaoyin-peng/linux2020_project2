#include<stdio.h>
#include<syscall.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<stdlib.h>

int main()
{
    int rand_num, pid;
    int count = 0;
    struct timeval t1, t2;
    FILE *fp;
    char file_name[11], str[300];

    pid = getpid();
    gettimeofday(&t1, NULL);
    
    sprintf(file_name, "file_%d.txt", pid);
    fp = fopen(file_name, "w");

    while(1)
    {
        gettimeofday(&t2, NULL);
        if((t2.tv_sec - t1.tv_sec) > 180)
            break;
        srand(time(NULL) + pid);
        rand_num = (rand() % 3) + 1;
        sprintf(str, "process %d is added into wait queue project2_queue_%d the %d th at time %ld\n", pid, rand_num, count++, t2.tv_sec);
        fputs(str, fp);

        syscall(436, rand_num); 
    }
    fclose(fp);
    printf("process %d completes!\n", pid);

}
