    #include<stdio.h>  
    #include<stdlib.h> 
    #include"TCB.h"


    int counter =1;
    //define the node
    struct node  
    {  
        struct TCB_t* tcb_t; 
        int data;
        struct node *next;  
        struct node *prev;  
    };


    /* Allocating space for TCB structure of new item to be added to the queue */
    struct node* newItem(){
      struct node* qElement = (struct node *) malloc(sizeof(struct node));
      qElement->data =counter++;
      qElement->next=NULL;
      qElement->prev=NULL;
      return qElement;
    }
    /* Creating a new empty queue */
    struct node* newQueue(){
      return NULL;
    }

    /* Adding element to end of the queue  */
    void AddQueue(struct node** head,struct node* item)  
    {  
  
       if(item == NULL){
        return;
       }


       if((*head) == NULL)  
       {  
           
           (*head)=item;
           (*head)->next = item;
           (*head)->prev = item;
       }  
       else  
       {  
          

          item->prev = (*head)->prev;
          item->next = (*head);
          (*head)->prev->next = item;
          (*head)->prev = item; 

       }          
    }

    /* Deleting the head of the queue and returning the deleted item,
Making the next item the new head of the queue */
    struct node* deleteItem(struct node** head) {
      struct node* temp_head = (*head);
      if((*head) == NULL)
        return NULL;

      else if((*head)->next==(*head) && (*head)->prev){ //redundant
        (*head) = NULL;
      }
      else {
        (*head)->prev->next = (*head)->next;
        (*head)->next->prev = (*head)->prev;
        (*head) = (*head)->next;
        
      }

      return temp_head;
    }



    