#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int trace_off =1; // initialized trace_off variable
int count_calls[29] = {0}; // initialized the count_calls array
int partial_sum[7] ={0}; // stores the partial sums for each subarray
extern void ps(void);
extern int sendp();
extern int recvp();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int 
sys_toggle(void)
{
if(trace_off==1) 
	{
	  	trace_off=0;
	}
else
	{
		for(int i =0 ; i<27;i++)
		{
			count_calls[i]=0;    /// so that the perivous count gets erased
		}
		trace_off=1;
	}
return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int               
sys_print_count(void)    // hard coded as the number of systesm calls won't change once a kernel is booted
{
if(count_calls[23]!=0){
    cprintf("%s %d\n","sys_add",count_calls[23]);
 }
	
 if(count_calls[8]!=0){
    cprintf("%s %d\n","sys_chdir",count_calls[8]);
 }
if(count_calls[20]!=0){
    cprintf("%s %d\n","sys_close",count_calls[20]);
 }   
if(count_calls[9]!=0){
    cprintf("%s %d\n","sys_dup",count_calls[9]);
 }
if(count_calls[6]!=0){
    cprintf("%s %d\n","sys_exec",count_calls[6]);
 }
if(count_calls[1]!=0){
    cprintf("%s %d\n","sys_exit",count_calls[1]);
 } 
if(count_calls[0]!=0){
    cprintf("%s %d\n","sys_fork",count_calls[0]);
 }
if(count_calls[7]!=0){
    cprintf("%s %d\n","sys_fstat",count_calls[7]);
 }
if(count_calls[10]!=0){
    cprintf("%s %d\n","sys_getpid",count_calls[10]);
 }
if(count_calls[5]!=0){
    cprintf("%s %d\n","sys_kill",count_calls[5]);
 }
if(count_calls[18]!=0){
    cprintf("%s %d\n","sys_link",count_calls[18]);
 }
if(count_calls[19]!=0){
    cprintf("%s %d\n","sys_mkdir",count_calls[19]);
 }
if(count_calls[16]!=0){
    cprintf("%s %d\n","sys_mknod",count_calls[16]);
 } 
if(count_calls[14]!=0){
    cprintf("%s %d\n","sys_open",count_calls[14]);
 }
if(count_calls[3]!=0){
    cprintf("%s %d\n","sys_pipe",count_calls[3]);
 }
if(count_calls[22]!=0){
    cprintf("%s %d\n","sys_print_count",count_calls[22]);
 }
if(count_calls[24]!=0){
    cprintf("%s %d\n","sys_print_ps",count_calls[24]);
 }

if(count_calls[4]!=0){
    cprintf("%s %d\n","sys_read",count_calls[4]);
 }
if(count_calls[26]!=0){
    cprintf("%s %d\n","sys_recv",count_calls[26]);
 }
if(count_calls[11]!=0){
    cprintf("%s %d\n","sys_sbrk",count_calls[11]);
 }
if(count_calls[25]!=0){
    cprintf("%s %d\n","sys_send",count_calls[25]);
 }
if(count_calls[12]!=0){
    cprintf("%s %d\n","sys_sleep",count_calls[12]);
 }
if(count_calls[21]!=0){
    cprintf("%s %d\n","sys_toggle",count_calls[21]);
 }
if(count_calls[17]!=0){
    cprintf("%s %d\n","sys_unlink",count_calls[17]);
 }
if(count_calls[13]!=0){
    cprintf("%s %d\n","sys_uptime",count_calls[13]);
 }
if(count_calls[2]!=0){
    cprintf("%s %d\n","sys_wait",count_calls[2]);
 }
if(count_calls[15]!=0){
    cprintf("%s %d\n","sys_write",count_calls[15]);
 }
return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int 
sys_add(int a, int b)
{
	int c =0;     // argint() is a method to take in input parameters inherent to xv6
	 if(argint(0, &a) < 0){ // a check just as the xv6 does
		 return -1;}
  	if(argint(1, &b) < 0){	// a check just as the xv6 does
    		return -1;}
	c=a+b;
return c;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
sys_ps(void)
{
	ps();    // helper function as one needs to access ptable which can only be done in proc.c
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int 
sys_send(int sender_pid, int rec_pid, void *msg)
{
	char* ptr = (char*)msg;
	if(argint(0, &sender_pid) < 0){  // a check just as the xv6 does
                return -1;}
	if(argint(1, &rec_pid) < 0){  // a check just as the xv6 does
                return -1;}
	if(argstr(2,&ptr) < 0){  // a check just as the xv6 does
                return -1;}
	return  sendp(sender_pid,rec_pid,ptr);     // helper function implemented in proc.c
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int 
sys_recv(void *msg)
{
	 char* ptr = (char*)msg;
	 if(argstr(0,&ptr) < 0){  // a check just as the xv6 does
                return -1;}
          return recvp(ptr);   // helper function implemented in proc.c
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
sys_store(int a, int b)
{
 	if(argint(0,&a)<0){}
	if(argint(1,&b)<0){}
	partial_sum[a]=b;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int 
sys_sums(void)
{
	int res=0;
	for(int i=0;i<7;i++)
	{
		res+=partial_sum[i];
	}
	return res;
}
