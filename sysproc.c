#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include "stat.h"

int sys_fork(void)
{
  return fork();
}

int sys_settickets(void)
{
  int number;
  argint(0, &number);

  if (number < 0)
    return -1; // unsuccessful
  else if (number == 0)
    return settickets(InitialTickets); // default
  else
  {
    return settickets(number);
  }
}

int sys_getpinfo(void)
{
  struct pstat *ps;
  if (argptr(0, (char **)&ps, sizeof(struct pstat)) < 0)
    return -1;
  getpinfo(ps);
  return 0;
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
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
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// int sys_nice(void)
// {
//   int n;
//   if (argint(0, &n) < 0)
//     return -1;
//   // cprintf("Value :%d\n",n);
//   struct proc *p = myproc();
//   p->nice_pro1 = n;
//   return p->nice_pro1;
// }

// int sys_my_rand(void)
// {
//   static int y = 2463534242UL;
//   y ^= (y << 13);
//   y ^= (y >> 17);
//   int random_val = (int)(y ^= (y << 15));
//   if (random_val < 0)
//     random_val = random_val * (-1);

//   // cprintf("Generated random number: %d\n", random_val);
//   return random_val;
// }

// int sys_print_cpu_status(void)
// {
//   return print_cpu_status();
// }

int sys_yield(void)
{
  yield();
  return 0;
}
