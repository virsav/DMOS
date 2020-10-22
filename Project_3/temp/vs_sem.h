#include "threads.h"

typedef struct semaphore_t {
    TCB_t *queue;
    int count;
} Semaphore_t;

Semaphore_t* CreateSem(Semaphore_t **new_sem, int i){

	(*new_sem) = (Semaphore_t*)malloc(sizeof(Semaphore_t));
	(*new_sem)->count = i;
	(*new_sem)->queue = newQueue();
	return (*new_sem);
}

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

void V(Semaphore_t **sem){

	(*sem)->count++;
	if((*sem)->count <= 0){
		TCB_t* blocked;
		blocked = DelQueue(&((*sem)->queue));
		AddQueue(&ReadyQ, &blocked);
	}
	yield();
}