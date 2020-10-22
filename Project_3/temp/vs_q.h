#include "TCB.h"

/* Allocating space for TCB structure of new item to be added to the queue */
TCB_t* NewItem(){

    TCB_t* new_item = (TCB_t*)malloc(sizeof(TCB_t));
    return new_item;
}

/* Creating a new empty queue */
TCB_t* newQueue(){

    TCB_t* header;
    header = NULL;
    return header;
}

/* Adding element to end of the queue  */
void AddQueue(TCB_t **head, TCB_t **item)
{
    if((*head) == NULL){
        (*head) = (*item);
        (*head)->next = (*head);
        (*head)->prev = (*head);
    }
    else{
        (*item)->prev = (*head)->prev;
        (*item)->next = (*head);
        (*head)->prev->next = (*item);
        (*head)->prev = (*item);
    }
}

/* Deleting the head of the queue and returning the deleted item,
Making the next item the new head of the queue */
TCB_t* DelQueue(TCB_t **head){

    if(head == NULL){
        perror("Queue is empty");
        exit(EXIT_FAILURE);
    }
    else if((*head)->next == (*head) && (*head)->prev == (*head)){
        TCB_t* temp = (*head);
        temp->next = NULL;
        temp->prev = NULL;
        head = NULL;
        return temp;
    }
    else{
        TCB_t* temp = (*head);
        temp->prev->next = (*head)->next;
        temp->next->prev = (*head)->prev;
        (*head) = (*head)->next;
        return temp;
    }
}

/* Freeing the allocated space of the TCB structure of the item */
void FreeItem(TCB_t **item){
    (*item) = NULL;
    free(&(*item));
}