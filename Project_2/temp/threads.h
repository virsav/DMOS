#include "q.h"

TCB_t* ReadyQ;
TCB_t* Curr_Thread;
int counter = 0;

void start_thread(void (*function)(void))
{
    int stack_size = 8192;
    void *stack = (void *)malloc(stack_size);
    TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
    init_TCB (tcb, function, stack, stack_size);
    tcb->thread_id = counter+1;
    AddQueue(&ReadyQ, &tcb);
}

void run()
{
    Curr_Thread = DelQueue(&ReadyQ);
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

void yield()
{
    TCB_t* Prev_Thread;
    AddQueue(&ReadyQ, &Curr_Thread);
    Prev_Thread = Curr_Thread;
    Curr_Thread = DelQueue(&ReadyQ);
    swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}