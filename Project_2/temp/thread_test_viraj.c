#include "threads.h"
int global =0;

void function_1(){
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
void function_2(){
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
void function_3(){
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
    start_thread(function_1);
    start_thread(function_2);
    start_thread(function_3);
    run();
    return 0;
}