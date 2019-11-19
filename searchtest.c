#include<stdio.h>
#include<stdlib.h>
#include "multitest.h"

int*ptr; //holds initial array numbers
//int fin=0;

int makeRandoms(int upper){
        int num = (rand() %
           (upper + 1));

    return num;
}

void swapindex(int* arr, int check, int arrSize){
	//take index, pick a random number within arraysize, make sure it is not == index, and then swap
	int newIndex = -1;
	do{
	
		newIndex = makeRandoms(arrSize);

	}while(newIndex != check);

	//swap the numbers
	  int temp = numbers[check];
   	  numbers[check] = numbers[newIndex];
    	  numbers[newIndex] = temp;
	  return; //should be updating the array, check this 

}

//array generator out here


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

int main (int argc, char** argv){
	int arrSize = 10000;
	int numThreads = 800;
	int target = 90;
	int numbers[arrSize];
	makeAndScramble(numbers,arraySize);

	 printf("PRINTING ORIGINAL ARRAY\n");
   //resultStruct *res = malloc(sizeof(resultStruct)); //struct to pass args to function

printf("-----------------------------------------------------------------\n");
 	int d=0;
	ptr=&(numbers[0]);
	for(d=0; d<arraySize; d++){
		printf("%d\t",ptr[d]);
		//res.arr[d]=numbers[d];
		//printf("%d\t",res.arr[d]); //-- values have been copied
	}
 	printf("\n");
	// this is printing the array
 printf("-----------------------------------------------------------------\n");

	int check = 0;
	int t=0;
for(t=0; t<10; t++){

	check = search (arrSize, numThreads, target, numbers);
	if(check == -1){
		printf("oh shet, there was an error boi.\n");
	}else{
		//means we got the index
		swapIndex(numbers, check, arraySize); //take the target and swap somewhere else -- prevents from generating an array again
	}
}
	return 0;

	//will eventually have to swap index and change things


	//all of this is one case only. Remember, we are generating the array
}
