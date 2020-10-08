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

Author 1: Raunak         ; ASU ID -1217240245
Author 2: Viraj Savaliya ; ASU ID -1217678787

Project 2 : Queue routines for multiple threads using non-preemptive scheduling
Date : 10/4/2020

Description : 	First the main thread creates a new queue and then starts 3 threads inside it. When threads are started, 
                a TCB structure for each thread is allocated and initialized, threads are assigned its ID number and 
                added at  the end of the queue. Then when you call run it will start the first thread which is the first
                item in the queue. Inside each thread when you call yield, then it will add the current thread to the 
                end of the queue and delete it from its head and make the next item/thread in the queue the new head. 
                This goes on continuously in the program provided for infinite time. 

-------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------Instructions--------------------------------------------------------------

How to run: 
gcc thread_test.c -o thread_test
./thread_test

-------------------------------------------------------------------------------------------------------------------------
#########################################################################################################################
*/


#include "threads.h"
int global =0;

/* Function for Thread 1 */
void function_1(){
    int local = 0;
    while(1) {
        printf("Printing from Function 1 global = %d local = %d\n", global, local);
        sleep(1);
        global++; local++;
        printf("Function 1 yielding .... global = %d local = %d\n", global, local);
        sleep(1);
        yield();																		//Yielding to next thread in the queue
        printf("function 1 remainder\n");
        sleep(1);
        yield();
    }
}

/* Function for Thread 2 */
void function_2(){
    int local = 0;
    while(1) {
        printf("Printing from Function 2 global = %d local = %d\n", global, local);
        sleep(1);
        global++; local++;
        printf("Function 2 yielding .... global = %d local = %d\n", global, local);
        sleep(1);
        yield();
        printf("function 2 remainder\n");
        sleep(1);
        yield();
    }
}

/* Function for Thread 3 */
void function_3(){
    int local = 0;
    while(1) {
        printf("Printing from Function 3 global = %d local = %d\n", global, local);
        sleep(1);
        global++; local++;
        printf("Function 3 yielding .... global = %d local = %d\n", global, local);
        sleep(1);
        yield();
        printf("function 3 remainder\n");
        sleep(1);
        yield();
    }
}

int main() {

	/* Creating a new queue */
    ReadyQ = newQueue();

    /* Starting each thread with its respective function */
    start_thread(function_1);
    start_thread(function_2);
    start_thread(function_3);

    /* Starting the queue routine */
    run();

    return 0;
}
