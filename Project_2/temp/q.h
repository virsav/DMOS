#include "TCB.h"

TCB_t* NewItem(){

    TCB_t* new_item = (TCB_t*)malloc(sizeof(TCB_t));
    return new_item;
}

TCB_t* newQueue(){

    TCB_t* header;
    header = NULL;
    return header;
}

void AddQueue(TCB_t **head, TCB_t **item)
{
    if((*head) == NULL){
        (*head) = (*item);
        (*head)->next = (*head);
        (*head)->prev = (*head);
    }
    else if((*head)->next == NULL){
        (*item)->prev = (*head);
        (*item)->next = (*head);
        (*head)->prev = (*item);
        (*head)->next = (*item);

    }
    else{
        (*item)->prev = (*head)->prev;
        (*item)->next = (*head);
        (*head)->prev->next = (*item);
        (*head)->prev = (*item);
    }
}

TCB_t* DelQueue(TCB_t **head){

    if((*head)->next == (*head) && (*head)->prev == (*head)){
        TCB_t* temp = (*head);
        temp->next = NULL;
        temp->prev = NULL;
        head = NULL;
        return temp;
    }
    else if(head == NULL){
        return NULL;
    }
    else{
        TCB_t* temp = (*head);
        temp->prev->next = (*head)->next;
        temp->next->prev = (*head)->prev;
        (*head) = (*head)->next;
        return temp;
    }
}

void FreeItem(TCB_t **item){
    (*item) = NULL;
    free(&(*item));
}