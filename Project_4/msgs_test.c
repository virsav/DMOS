/*
#########################################################################################################################
***********************************************Course Information********************************************************

                            CSE 531: Distributed Multiprocessor Operating Systems           
                                                Sem - Fall 2020                     
                                            Arizona State University                    
                                        Instructor: Dr. Partha Dasgupta                 

*************************************************************************************************************************
#########################################################################################################################
*/

/*
#########################################################################################################################
-----------------------------------------------Assignment Information----------------------------------------------------

Author 1: Raunak         ; ASU ID -
Author 2: Viraj Savaliya ; ASU ID -

Project 4 : Message passing via ports for multiple Server-Client model
Date : 11/11/2020

Description :   The total number of Servers and Clients are defined at the top of the code. All the servers and clients
                with their respective ports are first initialized and their repsective threads are started. Every client 
                is randomly assigned a Server to communicate with at the start and it remains fixed till the end. First,
                the Server waits for some client to send a message and when received from some client, the Server prints
                the message and replies the client back with a modified message by adding 10 to each of the message 
                elements. The client then prints the replied message on reception. At a time maximum 10 clients can 
                communicate with a single server.

-------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------Instructions--------------------------------------------------------------

How to run: 
gcc msgs_test.c -o msgs_test
./msgs_test

-------------------------------------------------------------------------------------------------------------------------
#########################################################################################################################
*/

#include<stdio.h>
#include<stdlib.h>
#include<zconf.h>
#include "msgs.h"

#define Max_Servers 2           //Total Servers
#define Max_Clients 13          //Total Clients

int port_client=0;              //client port number defined
struct queue *port[100];        //100 ports defined
semaphore_t* mutex;
int servers = 0;

//function of the client
void client(){
    int msg[10] = {0,1,2,3,4,5,6,7,8,9};                                //message to be sent to the server
    int i = port_client++;
    int server_port = 99 - (int)(rand()%Max_Servers);
    while(1) {

        if(i>(99-servers))
        {
            printf("\nUnfortunately! No ports available :(");           //print error and exit if no ports available
            break;
        }
        send(port[server_port],&msg[0], port[i]);                       //send the message to server
        printf("\n\t\t\t\tClient %d Sending message to server %d", i, (99- server_port));
        struct message reply = recv(port[i]);                           //receive the reply from server
        int len = sizeof(reply.mess)/sizeof(reply.mess[0]);
        printf("\nClient%d: printing message returned from server from port%d  :", i, i);
        for(int i=0; i<len; i++){
            printf("%d ", reply.mess[i]);
        }
        sleep(1);                                                       //wait for 1 second
    }

}

void server(){
    P(mutex);
    int server_port = 100 - (servers + 1);                              //Select Server port for each server
    int server_num = servers++;
    V(mutex);
    while(1) {
        
        struct message reply = recv(port[server_port]);                 //receive the reply from the client
        int msg[10];
        int len = sizeof(reply.mess)/sizeof(reply.mess[0]);
        printf("\nServer %d: Recieved data from the client :", server_num);
        for(int i=0; i<len; i++){
            printf("%d ",reply.mess[i]);                                //print the reply
        }
        for(int i=0; i<len; i++){
            msg[i] = reply.mess[i]+10;                                  //change the message response
        }
        send(reply.port_client, &msg[0], port[0]);                      //send the response from server to the client
        printf("\n\t\t\t\tServer %d Sending message to client", server_num);
    }
}



int main() {

    //initialize the ports
    for(int i=0; i<100; i++){
        port[i] = ports();
    }
    mutex = create_sem(1);

    //start the servers
    for (int i =0; i< Max_Servers; i++){
        start_thread(server);
    }

    //start the clients
    for (int i =0; i< Max_Clients; i++){
        start_thread(client);
    }
    run();

}
