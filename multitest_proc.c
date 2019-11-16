// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// Generates and prints 'count' random
// numbers in range [lower, upper].
int makeRandoms(int upper){
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
}
//int multitest(int arraySize, int procSize){
int main() {
  //initializing array
  int arraySize = 10;
  int numbers[arraySize];
  makeAndScramble(numbers,arraySize);

  int z;
  for (z=0; z<arraySize; z++) {
    printf("%d\n", numbers[z]);
  }


    int procSize = 2;
    int target = 5;
    int processAmount = arraySize/procSize;
    int currIndex = 0;
    int upperIndex = procSize-1;
    int i;
    for (i=0; i< processAmount; ++i) {
      if (fork()==0) {
        int l;
        if (i == processAmount-1) {
        //  printf("%d\n", i);
          upperIndex = arraySize-1;
        }
        for (l = currIndex; l <= upperIndex; l++) {
          //printf("%d\n", upperIndex);
          if (numbers[l]==target) {
           printf("%d\n", l);
            return 0;
          //  printf("poop");
          }
        }
        exit(0);

      }
      currIndex = upperIndex + 1;
      upperIndex = currIndex + procSize - 1;

    }

    int status;
    for (i=0; i < processAmount; ++i) {
      wait (&status);
    }





    return 0;
}
