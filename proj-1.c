#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

int flag=1;
semaphore_t mutex;

void function_1(int *arr)
{
    while (1){ 
        P(&mutex);
        printf("XXXXPrinting from Function 1 arr[0] = %d \n", *(arr + 0));
        sleep(1);
        arr[0]++;
        flag++;
        printf("Function 1 incremented .... arr[0] = %d \n", *(arr + 0));
        sleep(1);
	V(&mutex);
    }
}    

void function_2(int *arr)
{
    while (1){ 
        P(&mutex);
        printf("XXXXPrinting from Function 2 arr[1] = %d \n", *(arr + 1));
        sleep(1);
        arr[1]++;
        flag++;
        printf("Function 2 incremented .... arr[1] = %d \n", *(arr + 1));
        sleep(1);
	V(&mutex);
    }
}    

void function_3(int *arr)
{
    while (1){ 
        P(&mutex);
        printf("XXXXPrinting from Function 3 arr[2] = %d \n", *(arr + 2));
        sleep(1);
        arr[2]++;
        flag++;
        printf("Function 3 incremented .... arr[2] = %d \n", *(arr + 2));
        sleep(1);
	V(&mutex);
    }
}    

int main()
{
	int arr[3]={0,0,0};

    init_sem(&mutex, 1);
    start_thread(function_1, &arr);
    start_thread(function_2, &arr);
    start_thread(function_3, &arr);

    while(1) {

    	if(flag==4){
    		sleep(1);
    		printf("The values in the array are %d, %d, %d .\n", arr[0], arr[1], arr[2]);
    		flag=1;
    	}

    }

    return 0;
}