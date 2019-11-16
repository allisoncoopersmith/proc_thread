// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generates and prints 'count' random
// numbers in range [lower, upper].
int makeRandoms(int upper){
        int num = (rand() %
           (upper + 1));

    return num;
}


void makeAndScramble (int* numbers, int arraySize) {
  int x;
  for (x=0; x<arraySize; x++) {
    numbers[x] = x;
  }
  int y;
  for (y= 0; y < (arraySize/4)*3; y++) {
    int index1= makeRandoms(arraySize);
    int index2 = makeRandoms(arraySize);
    int temp = numbers[index1];
    numbers[index1] = numbers[index2];
    numbers[index2] = temp;
  }
}
//int multitest(int arraySize, int procSize){
int main() {
    int arraySize = 20;
    int numbers[arraySize];

    makeAndScramble(numbers,arraySize);

    int x;
    for (x=0; x<arraySize; x++) {
      numbers[x] = x;
    }
    int y;
    for (y= 0; y < (arraySize/4)*3; y++) {
      int index1= makeRandoms(arraySize);
      int index2 = makeRandoms(arraySize);
      int temp = numbers[index1];
      numbers[index1] = numbers[index2];
      numbers[index2] = temp;
    }

    int z;
    for (z=0; z<arraySize; z++){
      
    }


    return 0;
}
