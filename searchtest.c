#include<stdio.h>
#include<stdlib.h>
#include "multitest.h"

int*ptr; //holds initial array numbers
//int fin=0;

int makeRandoms(int upper){
        int num = (rand() %(upper + 1));
	return num;
}

void swapindex(int* numbers, int check, int arraySize){
	//take index, pick a random number within arraysize, make sure it is not == index, and then swap
	int newIndex = -1;
	do{
	
		newIndex = makeRandoms(arraySize);
		printf("New index is: %d, old index was %d\n", newIndex, check);

	}while(newIndex == check);

	//swap the target with a random number in the array until the target != the swapped array
		printf("Numbers check : %d\n", numbers[check]);
		printf("New index: %d\n", numbers[newIndex]);

		int temp = numbers[check];
		numbers[check] = numbers[newIndex];
		numbers[newIndex] = temp;

	  return; 

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

void printyboi(int * ptr, int arraySize){
	printf("----------------------------------------------------------------------------------\n");
	int d=0;
	for(d=0; d<arraySize; d++){
		printf("%d\t",ptr[d]);
		//printf("%d\t",res.arr[d]); //-- values have been copied
	}
 	printf("\n");
	// this is printing the array
	printf("----------------------------------------------------------------------------------\n");

	return;
}

int main (int argc, char** argv){
	int arraySize = 10;
	int numThreads = 5;
	int target = 2;
	int numbers[arraySize];
	ptr=&(numbers[0]);
	makeAndScramble(numbers,arraySize);

	if(arraySize<numThreads || (arraySize < 0) || (numThreads<0) || (target<0 || target > (arraySize-1))){
		printf("Error! Something with the bounds is off.\n");
		return -1;
	}

	
	int check = 0;
	int t=0;
	ptr=&(numbers[0]);
	for(t=0; t<2; t++){

		printyboi(ptr, arraySize);

		/*this is the search function*/check = search (arraySize, numThreads, target, numbers);
		check = 2;
		if(check == -1){
			printf("oh shet, there was an error boi.\n");
		}else{
		//means we got the index
			swapindex(&(numbers[0]), check, arraySize); //take the target and swap somewhere else -- prevents from generating an array again
		}


       }//end for loop -- this is for a test. Have five loops to test on different indices with different targets
	return 0;


}
