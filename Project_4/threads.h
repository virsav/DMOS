#include<stdio.h>
#include"q.h"

struct node* ReadyQ = 0;          //Pointer to queue
struct node* Curr_Thread = 0;     //Pointer to current thread
int counter_thread=0;             //Thread id
/* Function to start a new thread, hence allocate space and initialise TCB structure
   for the thread and add it the queue */
void start_thread(void (*function)(void))
{  
  void *stack = malloc(8192);
  struct TCB_t *tcb= (struct TCB_t *) malloc(sizeof(struct TCB_t)); 
  tcb->thread_id = ++counter_thread;
  init_TCB(tcb,function,stack,8192);
  struct node* newItem1 = newItem();
  newItem1->tcb_t = tcb;
  AddQueue(&ReadyQ,newItem1);
}
/* Function to run the head of the queue */
void run()
{   
  ucontext_t parent;     
  getcontext(&parent);  
  swapcontext(&parent, &(ReadyQ->tcb_t->context));
}

/* Function to swap the context and run the next item in the queue */
void yield() 
{
  struct node *Prev_Thread = ReadyQ;
  AddQueue(&ReadyQ, deleteItem(&ReadyQ));
  swapcontext(&(Prev_Thread ->tcb_t->context),&(ReadyQ ->tcb_t->context));
}
