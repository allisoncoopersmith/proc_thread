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


/*int makeRandoms(int upper){
        int num = (rand() %
           (upper + 1));

    return num;
}


void makeAndScramble (int* numbers, int arraySize) {
  srand(time(NULL));
  int x;
  for (x=0; x<arraySize; x++) {
    numbers[x] = x;
  }
  int y;
  int stop = ((arraySize/4)*3);

  for (y= 0; y < stop; y++) {
    int index1= makeRandoms(arraySize-1);
    int index2 = makeRandoms(arraySize-1);
    int temp = numbers[index1];
    numbers[index1] = numbers[index2];
    numbers[index2] = temp;
  }
}*/
//int multitest(int arraySize, int procSize){
int search(int arrSize, int procSize1, int target1, int* numbers) {
  //initializing array
  int arraySize = arrSize;
  //int numbers[arraySize];
  //makeAndScramble(numbers,arraySize);


    int procSpace;
    int procSize = procSize1;
    int target = target1;
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
	printf("Target %d was found at array index %d\n", target, procSpace);
      }

    }





    return procSpace;
}
