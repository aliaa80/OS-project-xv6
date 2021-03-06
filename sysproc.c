#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int readCount=0;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_changePolicy(void)
{
  int policy;
  argint(0, &policy);
  changePolicy(policy);
  return 1;
}

int
sys_setPriority(void)
{
  int priority;
  argint(0, &priority);
  setPriority(priority);
  return 1;
}

int
sys_getPolicy(void)
{
  return getPolicy();
}

int
sys_wait2(void)
{
  int* runningTime;
  int* sleepingTime;
  int* terminationTime;
  int* creationTime;
  int* readyTime;
  argptr(0, (char**)&runningTime ,sizeof(int));
  argptr(1, (char**)&sleepingTime , sizeof(int));
  argptr(2, (char**)&terminationTime , sizeof(int));
  argptr(3, (char**)&creationTime , sizeof(int));
  argptr(4, (char**)&readyTime , sizeof(int));
  return wait2(runningTime,sleepingTime,terminationTime,creationTime,readyTime);
}

int
sys_wait3(void)
{
  int* priority;
  int* runningTime;
  int* sleepingTime;
  int* terminationTime;
  int* creationTime;
  int* readyTime;
  argptr(0, (char**)&priority ,sizeof(int));
  argptr(1, (char**)&runningTime ,sizeof(int));
  argptr(2, (char**)&sleepingTime , sizeof(int));
  argptr(3, (char**)&terminationTime , sizeof(int));
  argptr(4, (char**)&creationTime , sizeof(int));
  argptr(5, (char**)&readyTime , sizeof(int));
  return wait3(priority,runningTime,sleepingTime,terminationTime,creationTime,readyTime);
}


int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int
sys_getProcCount(void){
  return getProcCount();
}
int
sys_getReadCount(void){
  return getReadCount();
}

int 
sys_thread_create(void){
  void* p;
  if(argptr(0,(void*)&p,sizeof(*p))<0){
    return -1;
  }
  return thread_create(p);
}

int 
sys_thread_wait(void){
  return thread_wait();
}
