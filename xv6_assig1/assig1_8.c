#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	if(argc< 2){
		printf(1,"Need type and input filename\n");
		exit();
	}
	char *filename;
	filename=argv[2];
	int type = atoi(argv[1]);
	printf(1,"Type is %d and filename is %s\n",type, filename);

	int tot_sum = 0;	
	//float variance = 0.0;

	int size=1000;
	short arr[size];
	char c;
	int fd = open(filename, 0);
	for(int i=0; i<size; i++){
		read(fd, &c, 1);
		arr[i]=c-'0';
		read(fd, &c, 1);
	}	
  	close(fd);
  	// this is to supress warning
  	printf(1,"first elem %d\n", arr[0]);
  
  	//----FILL THE CODE HERE for unicast sum
	int pid_par = getpid();
        int a = fork();
	int b = fork();
	int c2 = fork();

	if(a>0 && b>0 && c2>0)
	{      // parent process -> also coordinating process
		char *msg = (char *)malloc(MSGSIZE);
	 	recv(msg);
 		recv(msg);                                                 // here the mechanism implemented is that the main process is the coordintaing process and all other 7 processes are 
		recv(msg);                                                 //  sub-processes each of the subprocess calculates sum of the part of array assigned to it and then sends a message to 
		recv(msg);                                                 // coordinating process, implying that it's done before sending this message it stores the sum obtained by it in a shared 
		recv(msg);                                                 // memory using 'store' system call and then the subprocess exits so here the coordinating process waits for message of each 
		recv(msg);                                                 // of subprocess so total 7 recieves after recieving 7 such messages it means the shared memory is populated with the correct
		recv(msg);                                                 // sums of each of subprocess so it uses 'sums' system call to get the final sum.	
		wait();
		wait();							   // parent of 3 processes ... to prevent zombies
		wait();
		tot_sum=sums();
	}
	else if (a>0 && b>0 && c2==0)
	{
		int sum =0;   // partial sum 
		for (int i =0 ; i<143;i++)
		{
			sum += arr[i];
		}
		//printf(1," %d \n",sum);
		char *msg_child = (char *)malloc(MSGSIZE);
                msg_child = "1";
		store(0,sum);
                send(getpid(),pid_par,msg_child);                         //message acts as a signal to the coordintaing process that this subprocess is done, store stores the sum obtained by this 
		exit();                                                   // process.
	}
	else if (a>0 && b==0 && c2>0)
	{
		int sum =0;   // partial sum 
                for (int i =143 ; i<286;i++)
                {
                        sum += arr[i];
                }
		//printf(1,"%d \n",sum);
		char *msg_child = (char *)malloc(MSGSIZE);
                msg_child = "2";
		store(1,sum);
                send(getpid(),pid_par,msg_child);
		wait();
		exit();
	}
	else if(a>0 && b==0&& c2==0)
	{
		int sum =0;   // partial sum 
                for (int i =286 ; i<429;i++)
                {
                        sum += arr[i];
                }
		char *msg_child = (char *)malloc(MSGSIZE);
                msg_child = "3";
		store(2,sum);
                send(getpid(),pid_par,msg_child);
		//printf(1," %d \n",sum);
		exit();
	}
	else if(a==0 && b>0 && c2>0)
	{
		int sum =0;   // partial sum 
                for (int i =429 ; i<572;i++)
                {
                        sum += arr[i];
                }
		char *msg_child = (char *)malloc(MSGSIZE);
                msg_child = "4";
		store(3,sum);
                send(getpid(),pid_par,msg_child);
		//printf(1,"%d \n",sum);
		wait();
		wait();                                            // parent of 2 processes.. to prevent zombies
		exit();
	}
	else if(a==0 && b>0 && c2==0)
	{
		int sum =0;   // partial sum 
                for (int i =572 ; i<715;i++)
                {
                        sum += arr[i];
                }
		char *msg_child = (char *)malloc(MSGSIZE);
                msg_child = "5";
		store(4,sum);
                send(getpid(),pid_par,msg_child);
		//printf(1,"%d \n",sum);
		exit();
	}
	else if (a==0 && b==0 && c2>0)
	{
		int sum =0;   // partial sum 
                for (int i =715 ; i<858;i++)
                {
                        sum += arr[i];
                }
		char *msg_child = (char *)malloc(MSGSIZE);
                msg_child = "6";
		store(5,sum);
                send(getpid(),pid_par,msg_child);
		//printf(1,"%d \n",sum);
		wait();
		exit();
	}
	else
	{
		int sum =0;   // partial sum 
                for (int i =858 ; i<1000;i++)
                {
                        sum += arr[i];               
	       	}
		char *msg_child = (char *)malloc(MSGSIZE);
                msg_child = "7";
		store(6,sum);
                send(getpid(),pid_par,msg_child);
		//printf(1,"%d \n",sum);
		exit();
	}

  	//------------------
	
  	if(type==0){ //unicast sum
		printf(1,"Sum of array for file %s is %d\n", filename,tot_sum);
	}
	exit();
}
