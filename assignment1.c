#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

int arr[3]={0};
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

void child0(){
	while(1){
	pthread_mutex_lock(&lock);
	arr[0]++;
	printf("Child 0 added 1 to array[0], value of array[0]:%d\n",arr[0]);
	pthread_mutex_unlock(&lock);
	sleep(1);
	}
}

void child1(){
	while(1){
	pthread_mutex_lock(&lock);
	arr[1]++;
	printf("Child 1 added 1 to array[1], value of array[1]:%d\n",arr[1]);
	pthread_mutex_unlock(&lock);
	sleep(1);
	}
}

void child2(){
	while(1){
	pthread_mutex_lock(&lock);
	arr[2]++;
	printf("Child 2 added 1 to array[2], value of array[2]:%d\n",arr[2]);
	pthread_mutex_unlock(&lock);
	sleep(1);
	}
}


int main(){

	int i;
	printf("Parent thread with PID: %d initialized\n",getpid());

	
	pthread_t tid_0 = init_thread(child0,NULL);
	printf("Child 0 with TID: %d initialized\n",tid_0);
	pthread_t tid_1 = init_thread(child1,NULL);
	printf("Child 1 with TID: %d initialized\n",tid_1);
	pthread_t tid_2 = init_thread(child2,NULL);
	printf("Child 2 with TID: %d initialized\n",tid_2);

	while(1){
	sleep(1);
	printf("Values in the Array: %d, %d, %d\n", arr[0], arr[1], arr[2]);
	}
}
