#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "multitest.h"

//final


//int multitest(int arraySize, int procSize){
int search(int arraySize, int procSize, int target, int* numbers) {
  //initializing array
  //int arraySize = arrSize;
  //int numbers[arraySize];
  //makeAndScramble(numbers,arraySize);
	printf("-process\n");
	printf("Array size: %d, Number of processes: %d, Target: %d\n", arraySize, procSize, target);


    int procSpace;
    //int procSize = procSize1;
   // int target = target1;
    int processAmount = arraySize/procSize;
    int currIndex = 0;
    int upperIndex = procSize-1;
    int i;
    pid_t sig;
    pid_t signals[processAmount];
    for (i=0; i< processAmount; ++i) {
      sig = fork();
      if (sig==0) {
        int l;
        if (i == processAmount-1) {
          upperIndex = arraySize-1;
        }
        for (l = currIndex; l <= upperIndex; l++) {
        //  printf("%d\n", l);
          if (numbers[l]==target) {

           //printf("found at %d\n", l);
	   
		
          exit(l-currIndex);
          }
        }
        exit(251);

      }
      else {
        signals[i] = sig;
      }

      currIndex = upperIndex + 1;
      upperIndex = currIndex + procSize - 1;


    }
    int k;
    for (k=0; k< processAmount; k++) {
      int status;
      waitpid(signals[k], &status, 0);
      if(WEXITSTATUS(status) != 251) {
	int exitStatus = WEXITSTATUS(status);
	procSpace = (k * procSize) + exitStatus;
	//printf("Target %d was found at array index %d\n", target, procSpace);
      }

    }





    return procSpace;
}
