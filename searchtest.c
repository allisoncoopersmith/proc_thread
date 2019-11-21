#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include "multitest.h"

int*ptr; //holds initial array numbers
int check; //holds final target values
int arraySize; //size of the array
int target; //target
int numThreads; //where this is the number of threads/procs

int makeRandoms(int upper){
        int num = (rand() %(upper + 1));
	return num;
}

void swapindex(int* numbers, int check, int arraySize){
	//take index, pick a random number within arraysize, make sure it is not == index, and then swap
	int newIndex = -1;
	do{
		newIndex = makeRandoms(arraySize);
	}while(newIndex == check);
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
	//used to print the array being searched 
	printf("----------------------------------------------------------------------------------\n");
	int d=0;
	for(d=0; d<arraySize; d++){
		printf("%d\t",ptr[d]);
	}
 	printf("\n");
	printf("----------------------------------------------------------------------------------\n");

	return;
}
/*
void A (int arraySize, int numThreads, int target, int *arr){
	//array size 100
	


}

void B (int arraySize, int numThreads, int target, int *arr){
	//arraysize 1000


}

void C (int arraySize, int numThreads, int target, int *arr){
	//arraySize 10000


}

void D (int arraySize, int numThreads, int target, int *arr){
	//arraySize 20000


}
*/
int main (int argc, char** argv){
	arraySize = 50; //this changes based on function
	numThreads = 6; //this will change based on method
	target = 2; //just make this the same each time
	int numbers[arraySize];
	ptr=numbers;
	makeAndScramble(numbers,arraySize); //done before each test
	

	if(arraySize<numThreads || (arraySize < 0) || (numThreads<0) || (target<0 || target > (arraySize-1))){
		printf("Error! Something with the bounds is off.\n");
		return -1;
	}

	
	check = 0;
	int t=0;
	


	

	for(t=0; t<5; t++){
		//x++;
		
	
		printyboi(ptr, arraySize);
		check = search (arraySize, numThreads, target, numbers);

		if(check == -1){
			//this case is impossible, as we are generating a number guaranteed to be somewhere in the array
			printf("Index error, number not found.\n");
		}else{
		//means we got the index
			printf("Target %d was found in the array at index: %d\n", target, check);
			swapindex(numbers, check, arraySize); //take the target and swap somewhere else -- prevents from generating an array again
		} //this goes inbetween tests


       }


	
	return 0;


}
