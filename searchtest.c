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


int main (int argc, char** argv){
	//have user enter arguments??
	//enter arraysize and num threads/processes

	if (argc !=3){
		printf("Invalid number of arguments\n");
	}

	
			
	
	arraySize = atoi(argv[1]); //this changes based on function
	numThreads = atoi(argv[2]); //this will change based on method
	//printf("Num threads: %d. array size %d\n", numThreads, arraySize);
	target = 0; //just make this the same each time -- guaranteed to always have this at least

	
	if(arraySize<numThreads || numThreads > arraySize|| (arraySize < 0) || (numThreads<0) || (target<0 || target > (arraySize-1)) || arraySize == 0){
		if(arraySize == 0){
			printf("Cannot have arraysize 0\n");
			return 0;
		}
		printf("Error! Something with the bounds is off.\n");
		return -1;
	}

	if(numThreads>250){
		printf("Max size of thread/proc is capped at 250\n");
		numThreads=250;
	}
	//int numbers[arraySize];
	//ptr=numbers;
	//makeAndScramble(numbers,arraySize); //done before each test
	check = 0;
	int t=0; //iterator

		int numbers[arraySize]; //where numbersA is the array for A
		makeAndScramble(numbers,arraySize);
		ptr=numbers;
		//printf("Test A\n");
		
		struct timeval start;
		struct timeval end;
		struct timeval time;

		double timeA=0.00;
		

		gettimeofday(&time, NULL);
		suseconds_t systime = time.tv_usec;
		srand(systime);
	


	
		check = 0;
		//int t=0;
		int timeAarr[100];
	


	

	for(t=0; t<100; t++){	
				gettimeofday(&start, NULL);
				check = search (arraySize, numThreads, target, numbers);
				gettimeofday(&end, NULL);
				//printf("Target %d was found at array index %d\n", target, check);
				timeAarr[t] = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
				timeA += (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
				//swapindex(numbersA, check, arraySize);
				 //get new index for next iteration
			
			

		if(check == -1){
			//this case is impossible, as we are generating a number guaranteed to be somewhere in the array
			printf("Index error, number not found.\n");
		}else{
		//means we got the index
			printf("Target %d was found in the array at index: %d\n", target, check);
			swapindex(numbers, check, arraySize); //take the target and swap somewhere else -- prevents from generating an array again
		} //this goes inbetween tests


       }

	  timeA = timeA/100.0; //get average over 100 tests
      	  printf("Microseconds for workload array size %d, thread/proc size %d: %f\n", arraySize, numThreads, timeA);
          return 0;


}
