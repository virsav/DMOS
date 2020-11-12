#include "threads.h"
#include<stdio.h>

struct node* curr;
//Initialize structure for the semaphore
typedef struct semaphore_t 
{
    int count;
    struct node* sem_q;
} semaphore_t;

//Create the semaphore
struct semaphore_t * create_sem(int inputValue)
{   

	struct semaphore_t* sem_t = (struct semaphore_t *) malloc(sizeof(struct semaphore_t));
	sem_t->count=inputValue;
    return sem_t;
}
//P routine of the semaphore
void P(semaphore_t * sem)
{
    
	sem->count--;
	if(sem->count<0)
	{
        curr = deleteItem(&ReadyQ);
        AddQueue(&sem->sem_q, curr); //adding the top element of the ready queue to the semaphore queue
        swapcontext(&(curr->tcb_t->context),&(ReadyQ->tcb_t->context)); //swapping the context with the next in the ready queue
    }
}
//V routine of the semaphore
void V(semaphore_t * sem)
{
	sem->count++;
	if(sem->count<=0)
	{
        AddQueue(&ReadyQ,deleteItem(&sem->sem_q)); //adding the top element of the semaphore queue to the ready queue
	}
    yield();
}

