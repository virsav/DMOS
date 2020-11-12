#include "sem.h"

//payload to be sent
struct message {
    int mess[10];
    struct queue *port_client;
};

//node of the queue containing message
struct qnode{
    struct message data;
    struct qnode *next;
};

//definition of queue containing message
struct queue {
    semaphore_t *sen, *recv, *mutex;
    int counter;
    struct qnode *head;
};

//definition of ports
struct queue* ports(){
    struct queue *new = (struct queue *)malloc(sizeof(struct queue));
    new->counter = 0;
    new->head = NULL;
    new->sen = create_sem(10);
    new->mutex = create_sem(1);
    new->recv = create_sem(0);
    return new;
}

//insert a node to the queue
void insertToPortQ(struct queue *port, struct qnode *item){
    if(port == NULL){
        printf("Port is NULL \n");
        return;
    }
    P(port->sen);
    P(port->mutex);
    struct qnode *nodez = port->head;
    if(nodez == NULL){
        port->head = item;
    }
    else{
        while(nodez->next != NULL){
            nodez = nodez->next;
        }
        nodez->next = item;
    }
    V(port->mutex);
    V(port->recv);
}

//delete the node from the front of the queue
struct message delQ(struct queue *port){

    if(port == NULL){
        perror("Port is NULL");
        exit(EXIT_FAILURE);
    }
    P(port->recv);
    P(port->mutex);

    struct message res = port->head->data;
    port->head = port->head->next;

    V(port->mutex);
    V(port->sen);
    return res;
}

//send the message from client portC to port
void send(struct queue *port, int *msg, struct queue *portC){
    struct qnode *new = (struct qnode *)malloc(sizeof(struct qnode));
    for(int i=0; i<10; i++){
        new->data.mess[i] = *(msg+i);
    }
    new->data.port_client = portC;
    new->next = NULL;
    return insertToPortQ(port, new);
}

//receive the message from the port
struct message recv(struct queue *port){
    return delQ(port);
}

