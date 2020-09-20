#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


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

struct args_struct{

	int *arr;
	int num;
	int n;
};

semaphore_t mutex,child_finish;

pthread_t init_thread(void *func, struct args_struct *arg){
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,func,(void*)arg);
	if(ret){
		printf("error\n");
		exit(-1);
	}
	return tid;
}

void* child(struct args_struct *args){
	
	for(int count=0; count<args->n;count++){
		P(&mutex);
		args->arr[args->num]++;
		printf("Child %d added 1 to array[%d], value of array[%d]:%d\n",args->num, args->num, args->num,args->arr[args->num]);
		sleep(1);
		V(&child_finish);
	}
}

int main(int argc, char *argv[]){

	if( argc == 3 ) {
     		printf("The argument supplied are %s %s\n", argv[1], argv[2]);
	   }
	else if( argc > 3 ) {
	      printf("Too many arguments supplied.\n");
	   }
	else {
	      printf("Two arguments expected.\n");
	   }

	char *nn = argv[1];
	int n = atoi(nn);
	char *nn1 = argv[2];
	int n1 = atoi(nn1);
	int *arr = (int *)malloc(sizeof(int)*n);
	struct args_struct *str = (struct args_struct *)malloc(sizeof(struct args_struct)*n);
	pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t)*n);
	init_sem(&mutex, n);
	init_sem(&child_finish, 0);
	printf("Parent thread with PID: %d initialized\n",getpid());

	for(int i=0; i<n; i++){
		
		str[i].arr = arr;
		str[i].num = i;
		str[i].n = n1;
		tid[i] = init_thread(child,&str[i]);
		printf("Child %d with TID: %ld initialized\n",i,tid[i]);
	}

	

		for(int i=0; i<n1; i++){

			for(int i =0; i<n; i++){
			P(&child_finish);
			}
			
			for(int i=0; i<n; i++){
				printf("Value in the Array %d: %d\n", i, arr[i]);
			}
			
			for(int i =0; i<n; i++){
			V(&mutex);
			}
		}
	
	for(int i=0; i<n; i++){
		pthread_join(tid[i], NULL);  //terminate the thread 
	}
	free(arr);
	free(str);
	return 0;
}
