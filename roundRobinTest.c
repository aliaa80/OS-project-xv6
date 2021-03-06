#include "types.h"
#include "stat.h"
#include "user.h"


int main(void){
    changePolicy(2);
    int father=getpid();
    int pids[10]={0};
    int waitings[10];
    int bursts[10];
    int turnarounds[10];
    int runningTime,sleepingTime,terminationTime,creationTime,readyTime;
    int waitingTimeAverage=0;
    int burstTimeAverage=0;
    int turnaroundTimeAverage=0;
    
    for(int i=0;i<10;i++){
        if(getpid()==father){
            fork();
        }
    }
    if(getpid()==father){
        for(int i=0;i<10;i++){
            pids[i]=wait2(&runningTime,&sleepingTime,&terminationTime,&creationTime,&readyTime);
            waitings[i]=sleepingTime+readyTime;
            bursts[i]=runningTime;
            turnarounds[i]=waitings[i]+bursts[i];
            waitingTimeAverage+=waitings[i];
            burstTimeAverage+=bursts[i];
            turnaroundTimeAverage+=turnarounds[i];
        }
    }else{
        for (int i=1; i<=1000; i++) {
            printf(1, "/%d/ : /%d/ \n", getpid(), i);
            // sleep(10);
        }
        exit();
    }
    for(int i=0;i<10;i++){
        printf(1,"\nPID : %d | Waiting : %d | CBT : %d | Turnaround : %d ",pids[i],waitings[i],bursts[i],turnarounds[i]);
    }
    
    waitingTimeAverage/=10;
    burstTimeAverage/=10;
    turnaroundTimeAverage/=10;
    printf(1,"\nAverage Waiting Time : %d",waitingTimeAverage);
    printf(1,"\nAverage CBT : %d",burstTimeAverage);
    printf(1,"\nAverage Turnaround Time : %d",turnaroundTimeAverage);
    exit();
}

