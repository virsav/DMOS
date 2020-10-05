#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

int flag=1;
semaphore_t mutex;

struct args{

    int *arr;
    int num;

};

void child_th(struct args *trd_arg)
{
    while (1){ 
        P(&mutex);
        sleep(1);
        trd_arg->arr[trd_arg->num]++;
        flag++;
        printf("Child %d incremented .... arr[%d] = %d \n", trd_arg->num, trd_arg->num, trd_arg->arr[trd_arg->num]);
        sleep(1);
	V(&mutex);
    }
}    

int main()
{
	int n = 3;
	int *arr = (int *)malloc(sizeof(int)*n);
	memset(arr,0,sizeof(int)*n);
    struct args *th_args = (struct args *)malloc(sizeof(struct args)*n);

    init_sem(&mutex, 1);

    for(int i=0; i<3;i++){
        th_args[i].arr = arr;
        th_args[i].num = i;
        start_thread(child_th, &th_args[i]);
    }


    while(1) {

    	if(flag==4){
    		sleep(1);
    		printf("The values in the array are %d, %d, %d .\n", arr[0], arr[1], arr[2]);
    		flag=1;
    	}

    }

    free(arr);

    return 0;
}
