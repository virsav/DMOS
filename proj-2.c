#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <string.h>
#include <pthread.h>
#include <zconf.h>

#define Size_Stack 8192

int global=0;

struct TCB_t{
    struct TCB_t* next;
    struct TCB_t* prev;
    int thread_id;
    ucontext_t context;
};

void init_TCB(struct TCB_t *tcb, void *function, void *stackP, int stack_size){
    memset(tcb, '\0', sizeof(struct TCB_t));
    getcontext(&tcb->context);
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t)stack_size;
    makecontext(&tcb->context, function, 0);
}

struct TCB_t* NewItem(void){
    struct TCB_t *new = (struct TCB_t*)malloc(sizeof(struct TCB_t));
    return new;
}

struct TCB_t* newQueue(void){
    //struct TCB_t *head =NULL;
    struct TCB_t *head = (struct TCB_t*)malloc(sizeof(struct TCB_t));
    head->thread_id = 0;
    head->next = NULL;
    head->prev = NULL;
    //head->context = NULL;
    head->next = head->prev;
    head->prev = head->next;
    return head;
}

void AddQueue(struct TCB_t **head, int item){
    struct TCB_t *add = (struct TCB_t*)malloc(sizeof(struct TCB_t));
    add->thread_id = item;
    struct TCB_t* temp = *head;
    while((*head) != temp->next){
        temp = temp->next;
    }
    add->next = *head;
    add->prev = temp;
    temp->next = add;
    (*head)->prev = add;
}
void AddQueue2(struct TCB_t **head, struct TCB_t **item){
    struct TCB_t* temp = *head;
    if(temp == NULL){
        (*head) = (*item);
        return;
    }
    if(temp->next == NULL){
        (*head)->next = (*item);
        (*head)->prev = (*item);
        (*item)->next = (*head);
        (*item)->prev = (*head);
        return;
    }
    while((*head) != temp->next){
        temp = temp->next;
    }
    (*item)->next = *head;
    (*item)->prev = temp;
    temp->next = *item;
    (*head)->prev = *item;
}

struct TCB_t* DelQueue(struct TCB_t **head){
    struct TCB_t *temp = (*head);
    struct TCB_t *next;
    if((*head) == NULL){
        return NULL;
    }
    if((*head)->next == NULL){
        return (*head);
    }
    if((*head)->next->next == NULL){
        temp = (*head)->next;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return temp;
    }
    temp = temp->next;
    next = temp->next;
    (*head)->next = next;
    next->prev = (*head);
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void FreeItem(struct TCB_t **item){
    (*item) = NULL;
    free(&(*item));
}

struct TCB_t *ReadyQ;
struct TCB_t *Curr_Thread;
volatile int global_thread_id=0;

void start_thread(void (*function)(void)){
    void *stack = (void*)malloc(Size_Stack);
    struct TCB_t *TCB = (struct TCB_t*)malloc(sizeof(struct TCB_t));
    init_TCB(TCB, function, stack, Size_Stack);
    global_thread_id++;
    TCB->thread_id = global_thread_id;
    AddQueue2(&ReadyQ, &TCB);
}

void run(){
    Curr_Thread = DelQueue(&ReadyQ);
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(Curr_Thread->context));
}

void yield(){
    struct TCB_t *Prev_Thread;
    AddQueue2(&ReadyQ,&Curr_Thread);
    Prev_Thread = Curr_Thread;
    Curr_Thread = DelQueue(&ReadyQ);
    swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}
void print_thread_id1(){
    int local = 0;
    while(1) {
        printf("Printing from Function 1 global = %d local = %d\n", global, local);
        sleep(1);
        global++; local++;
        printf("Function 1 yielding .... global = %d local = %d\n", global, local);
        sleep(1);
        yield();
        printf("function 1 remainder\n");
        sleep(1);
        yield();

    }
}
void print_thread_id2(){
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
void print_thread_id3(){
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
    ReadyQ = newQueue();
    start_thread(print_thread_id1);
    start_thread(print_thread_id2);
    start_thread(print_thread_id3);
    run();
    return 0;
}

