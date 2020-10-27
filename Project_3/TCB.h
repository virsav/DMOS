#define _GNU_SOURCE
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* TCB structure for each item/thread in the queue */
typedef struct TCB_item {

    struct TCB_item* next;
    struct TCB_item* prev;
    int thread_id;
    ucontext_t context;
}TCB_t;

/* Function to initialise the TCB structure of the thread */
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)

// arguments to init_TCB are

//   1. pointer to the function, to be executed

//   2. pointer to the thread stack

//   3. size of the stack

{

    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);// context is now cooked

}