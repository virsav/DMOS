#########################################################################################################################
-----------------------------------------------Assignment Information----------------------------------------------------

Author 1: Raunak 	 ; ASU ID -1217240245
Author 2: Viraj Savaliya ; ASU ID -1217678787

Project 1 : Synchronization between Child and Parent threads using Pthreads and Semaphores
Date : 9/20/2020

Description : 	The main thread inititalizes an array of size 3 with 0. The main thread created 3 child threads to 
		increment the ith value in the array from the ith child. The order in which the values inside the array 
		incremented by the child threads is not fixed. When all the 3 child threads have incremented (the parent 
		thread waits)the their resepective ith values, the parent thread will print the values inside the array 
		and this process continues for infinite time or till user interupts. There is a sleep used after printing
		the values of the array so that the changes can be observed visually, removing the sleep does not make 
		any change to the functionality.

-------------------------------------------------------------------------------------------------------------------------
#########################################################################################################################

#########################################################################################################################
-----------------------------------------------Instructions--------------------------------------------------------------

How to run: 
gcc -pthread proj-1.c -o proj_1
./proj_1

Sample Output :
Parent thread with PID: 16673 initialized
Child 0 with TID: 140628363151104 initialized
Child 0 added 1 to array[0], value of array[0]:1
Child 1 with TID: 140628354758400 initialized
Child 1 added 1 to array[1], value of array[1]:1
Child 2 with TID: 140628346365696 initialized
Child 2 added 1 to array[2], value of array[2]:1
Values in the Array: 1, 1, 1
Child 1 added 1 to array[1], value of array[1]:2
Child 2 added 1 to array[2], value of array[2]:2
Child 0 added 1 to array[0], value of array[0]:2
Values in the Array: 2, 2, 2
Child 0 added 1 to array[0], value of array[0]:3
Child 1 added 1 to array[1], value of array[1]:3
Child 2 added 1 to array[2], value of array[2]:3
Values in the Array: 3, 3, 3
Child 0 added 1 to array[0], value of array[0]:4
Child 2 added 1 to array[2], value of array[2]:4
Child 1 added 1 to array[1], value of array[1]:4
Values in the Array: 4, 4, 4


-------------------------------------------------------------------------------------------------------------------------
#########################################################################################################################
