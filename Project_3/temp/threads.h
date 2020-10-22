#include "q.h"
#define stack_size 8192

TCB_t* ReadyQ;			//Pointer to queue
TCB_t* Curr_Thread;		//Pointer to current thread
int counter = 0;		//Thread id

/* Function to start a new thread, hence allocate space and initialise TCB structure
   for the thread and add it the queue */
void start_thread(void (*function)(void))
{
    void *stack = (void *)malloc(stack_size);
    TCB_t *tcb = NewItem();
    init_TCB (tcb, function, stack, stack_size);
    tcb->thread_id = ++counter;
    AddQueue(&ReadyQ, &tcb);
    printf("Starting Thread no %d\n", tcb->thread_id);
}

/* Function to run the head of the queue */
void run()
{
    Curr_Thread = DelQueue(&ReadyQ);
    ucontext_t parent;     
    getcontext(&parent);   
    swapcontext(&parent, &(Curr_Thread->context));

}

/* Function to swap the context and run the next item in the queue */
void yield()
{
    TCB_t* Prev_Thread;
    AddQueue(&ReadyQ, &Curr_Thread);
    Prev_Thread = Curr_Thread;
    Curr_Thread = DelQueue(&ReadyQ);
    printf("Switching from Thread %d to Thread %d\n", Prev_Thread->thread_id, Curr_Thread->thread_id);
    swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}