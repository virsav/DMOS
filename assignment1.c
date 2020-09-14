#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;
volatile int i=0;

typedef struct semaphore_t {
     pthread_mutex_t mutex;
     pthread_cond_t cond;
     int count;
} semaphore_t;

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


semaphore_t mutex,child_finish;

pthread_t init_thread(void *func, int *arg){
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,func,arg);
	if(ret){
		printf("error\n");
		exit(-1);
	}
	return tid;
}

void child0(int arr[]){
	while(1){
		
		P(&mutex);
		arr[0]++;
		printf("Child 0 added 1 to array[0], value of array[0]:%d\n",arr[0]);
		//i++;
		sleep(1);
		V(&child_finish);
	}
}

void child1(int arr[]){
	while(1){
		
		P(&mutex);
		arr[1]++;
		printf("Child 1 added 1 to array[1], value of array[1]:%d\n",arr[1]);
		//i++;
		sleep(1);
		V(&child_finish);
	}
}

void child2(int arr[]){
	while(1){
		
		P(&mutex);
		arr[2]++;
		printf("Child 2 added 1 to array[2], value of array[2]:%d\n",arr[2]);
		//i++;
		sleep(1);
		V(&child_finish);
	}
}


int main(){

	int arr[3]={0};
	init_sem(&mutex, 3);
	init_sem(&child_finish, 0);
	printf("Parent thread with PID: %d initialized\n",getpid());

	
	pthread_t tid_0 = init_thread(child0,arr);
	printf("Child 0 with TID: %d initialized\n",tid_0);
	pthread_t tid_1 = init_thread(child1,arr);
	printf("Child 1 with TID: %d initialized\n",tid_1);
	pthread_t tid_2 = init_thread(child2,arr);
	printf("Child 2 with TID: %d initialized\n",tid_2);

	while(1){
		//sleep(3);
		//if(i==3){
			//i=0;
			P(&child_finish);
			P(&child_finish);
			P(&child_finish);
			printf("Values in the Array: %d, %d, %d\n", arr[0], arr[1], arr[2]);
			V(&mutex);
			V(&mutex);
			V(&mutex);
		//}
		
	}
}
