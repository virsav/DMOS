
/*
#########################################################################################################################
***********************************************Course Information********************************************************

				CSE 531: Distributed Multiprocessor Operating Systems			
						Sem - Fall 2020 					
					    Arizona State University 					
		    		        Instructor: Dr. Partha Dasgupta					

*************************************************************************************************************************
#########################################################################################################################
*/

/*
#########################################################################################################################
-----------------------------------------------Assignment Information----------------------------------------------------

Author 1: Raunak 	 ; ASU ID -
Author 2: Viraj Savaliya ; ASU ID -

Project 1 : Synchronization between Child and Parent threads using Pthreads and Semaphores
Date : 9/20/2020

Description : 	The main thread inititalizes an array of size 3 with 0. The main thread created 3 child threads to 
		increment the ith value in the array from the ith child. The order in which the values inside the array 
		incremented by the child threads is not fixed. When all the 3 child threads have incremented (the parent 
		thread waits)the their resepective ith values, the parent thread will print the values inside the array 
		and this process continues for infinite time or till user interupts. There is a sleep used after printing
		the values of the array so that the changes can be observed visually, removing the sleep does not make 
		any change to the functionality.

-------------------------------------------------------------------------------------------------------------------------
#########################################################################################################################
#########################################################################################################################
-----------------------------------------------Instructions--------------------------------------------------------------

How to run: 
gcc -pthread proj-1.c -o proj_1
./proj_1

or

gcc proj-1.c -o proj_1 -lpthread
./proj_1

Sample Output :
Parent thread with PID: 9190 initialized
Child 0 with TID: 140314017482496 initialized
Child 0 added 1 to array[0], value of array[0]:1
Child 1 with TID: 140314009089792 initialized
Child 1 added 1 to array[1], value of array[1]:1
Child 2 with TID: 140314000697088 initialized
Child 2 added 1 to array[2], value of array[2]:1
Values in the Array: 1, 1, 1
Child 0 added 1 to array[0], value of array[0]:2
Child 2 added 1 to array[2], value of array[2]:2
Child 1 added 1 to array[1], value of array[1]:2
Values in the Array: 2, 2, 2
Child 0 added 1 to array[0], value of array[0]:3
Child 2 added 1 to array[2], value of array[2]:3
Child 1 added 1 to array[1], value of array[1]:3
Values in the Array: 3, 3, 3
Child 0 added 1 to array[0], value of array[0]:4
Child 1 added 1 to array[1], value of array[1]:4
Child 2 added 1 to array[2], value of array[2]:4
Values in the Array: 4, 4, 4



-------------------------------------------------------------------------------------------------------------------------
#########################################################################################################################
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

//structure of semaphore is defined
typedef struct semaphore_t {
     pthread_mutex_t mutex;
     pthread_cond_t cond;
     int count;     		//count value of semaphore
} semaphore_t;

//function to initialize the semaphore with a count value. 
void init_sem(semaphore_t *s, int i)
{   
    s->count = i;
    pthread_mutex_init(&(s->mutex), NULL);
    pthread_cond_init(&(s->cond), NULL);
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process 
 */
void P(semaphore_t *sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count--;
    if (sem->count < 0) pthread_cond_wait(&(sem->cond), &(sem->mutex));
    pthread_mutex_unlock (&(sem->mutex)); 
}


/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process and yields
 */
void V(semaphore_t * sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count++;
    if (sem->count <= 0) {
	pthread_cond_signal(&(sem->cond));
    }
    pthread_mutex_unlock (&(sem->mutex)); 
    pthread_yield();
}

//structure initialized to pass the parameters to each child created
struct args_struct{

	int *arr;   		//the array to be modified by the child thread
	int num;    		//the location of the array to be incremented by each child
	semaphore_t wait;  	//semaphore for each thread to execute once and wait for the parent process
};


//function which creates the thread and returns the thread_id is declared
pthread_t init_thread(void *func, struct args_struct *arg){
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,func,(void*)arg);   	//creates the thread
	if(ret){
		printf("error\n");
		exit(-1);
	}
	return tid;
}


//Semaphore which signals the parent process to wait for the child to finish
semaphore_t child_finish;


//Function which takes arguments of the args_struct structure and executes the child is declared
void child(struct args_struct *args){


	while(1){
	
		P(&args->wait);    							//test and decrement the individual semaphore of each thread
		args->arr[args->num]++;   						//increment the array value and print the incremented value
		printf("Child %d added 1 to array[%d], value of array[%d]:%d\n",args->num, args->num, args->num,args->arr[args->num]);
		V(&child_finish);  							//increment the parent process semaphore
	}//infinite loop
}
//end of child


//start of main
int main(){

	int arr[3]={0};    							//initialize the array
	init_sem(&child_finish, 0);   						//initialize the parent process semaphore
	printf("Parent thread with PID: %d initialized\n",getpid());  		//print the pid of the parent process
	sleep(1);
	//initialize the structure values for the first child
	struct args_struct args1;
	args1.arr = arr;
	args1.num = 0;
	init_sem(&args1.wait, 1);
	
	//intialize the structure values for the second child
	struct args_struct args2;
	args2.arr = arr;
	args2.num = 1;
	init_sem(&args2.wait, 1);

	//initialize the structure values for the third child
	struct args_struct args3;
	args3.arr = arr;
	args3.num = 2;
	init_sem(&args3.wait, 1);
	
	pthread_t tid_0 = init_thread(child,&args1);       		//create the first child thread
	printf("Child 0 with TID: %ld initialized\n",tid_0);   		//print tid of the child thread 1
	sleep(1);
	pthread_t tid_1 = init_thread(child,&args2);       		//create the second child thread
	printf("Child 1 with TID: %ld initialized\n",tid_1);  		//print tid of the child thread 2
	sleep(1);
	pthread_t tid_2 = init_thread(child,&args3);       		//create the third child thread
	printf("Child 2 with TID: %ld initialized\n",tid_2);		//print tid of the child thread 3

	while(1){
		
			P(&child_finish);    							//wait for 1 child to finish
			P(&child_finish);    							//wait for 2 childs to finish
			P(&child_finish);    							//wait for all the childs to finish 
			printf("Values in the Array: %d, %d, %d\n", arr[0], arr[1], arr[2]);   	//print the values of the array
			sleep(1);								//Sleep of 1 sec after printing values and before starting next cycle
			V(&args1.wait);      							//release 1 child
			V(&args2.wait);      							//release 2 childs
			V(&args3.wait);      							//release all the childs
		
	}//infinite loop
}
//end of main
