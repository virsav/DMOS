#include "TCB.h"

/* Allocating space for TCB structure of new item to be added to the queue */
TCB_t* NewItem(void){
    TCB_t *new = (TCB_t*)malloc(sizeof(TCB_t));
    return new;
}

/* Creating a new empty queue */
TCB_t* newQueue(void){
    TCB_t *head;
    head = NULL;
    return head;
}

/* Adding element to end of the queue  */
void AddQueue(TCB_t **head, TCB_t **item){
    TCB_t* temp = *head;
    if(temp == NULL){
        (*head) = (*item);
        (*head)->next = (*head)->prev;
        (*head)->prev = (*head)->next;
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

/* Deleting the head of the queue and returning the deleted item,
Making the next item the new head of the queue */
TCB_t* DelQueue(TCB_t **head){
    TCB_t *temp = (*head);
    TCB_t *end = (*head);
    TCB_t *next;
    if((*head) == NULL){
        return NULL;
    }
    if((*head)->next == NULL){
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return temp;
    }
    while((*head) != end->next){
        end =end->next;
    }
    (*head) = temp->next;
    end->next = (*head);
    (*head)->prev = end;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

/* Freeing the allocated space of the TCB structure of the item */
void FreeItem(TCB_t **item){
    (*item) = NULL;
    free(&(*item));
}