#include<ucontext.h>
#include<string.h>

/* TCB structure for each item/thread in the queue */
struct TCB_t
{
	ucontext_t context;
	int thread_id;
};
/* Function to initialise the TCB structure of the thread */
void init_TCB (struct TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    // arguments to init_TCB are

//   1. pointer to the function, to be executed

//   2. pointer to the thread stack

//   3. size of the stack
    memset(tcb, '\0', sizeof(tcb));    // wash, rinse
    getcontext(&tcb->context);              
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function,1, tcb->thread_id); // context is now cooked
}
