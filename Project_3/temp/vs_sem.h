#include "threads.h"

//Initialize structure for the semaphore
typedef struct Semaphore_t {
    TCB_t *queue;
    int count;
} Semaphore_t;

//Create the semaphore
Semaphore_t* CreateSem(int i){

    Semaphore_t (*new_sem) = (Semaphore_t*)malloc(sizeof(Semaphore_t));
	(new_sem)->count = i;
	(new_sem)->queue = newQueue();
	return (new_sem);
}

//P routine of the semaphore
void P(Semaphore_t **sem){

	(*sem)->count--;
	if((*sem)->count < 0){
		TCB_t* Prev_Thread;
		AddQueue(&((*sem)->queue), &Curr_Thread);
	    Prev_Thread = Curr_Thread;
	    Curr_Thread = DelQueue(&ReadyQ);
	    swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
	}
}

//V routine of the semaphore
void V(Semaphore_t **sem){

	(*sem)->count++;
	if((*sem)->count <= 0){
		TCB_t* unblocked;
		unblocked = DelQueue(&((*sem)->queue));
		AddQueue(&ReadyQ, &unblocked);
	}
	yield();
}
