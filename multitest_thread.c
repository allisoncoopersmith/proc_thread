#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "multitest.h"

// final update

//updated version because Diana is dumb

//int threadCount=0;
int count=0;
int*ptr; //holds initial array numbers
int fin=0; //holds final index (to be returned from main method)
int target;// = 17; // make this a macro
typedef struct resultStruct{
	int currIndex;
	int upperIndex; // 
	//int* arr; //original array to be passed
	int result; //flag
	//int target; //target to be searched for
        
}resultStruct;

void *threadFunction (void *); // this will be the search function
/*
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

*/

int search (int arrSize, int threadSize1, int target1, int * numbers)
{

	//printf("yes\n");
   int arraySize = arrSize;
   target = target1; //user specified
   ptr=numbers;
   //int numbers[arraySize];
   //makeAndScramble(numbers,arraySize);
   
   //printf("PRINTING ORIGINAL ARRAY\n");
   //resultStruct *res = malloc(sizeof(resultStruct)); //struct to pass args to function
/*
printf("-------------------------------------\n");
 	int d=0;
	ptr=&(numbers[0]);
	for(d=0; d<arraySize; d++){
		printf("%d\t  ",ptr[d]);
		//res.arr[d]=numbers[d];
		//printf("%d\t",res.arr[d]); //-- values have been copied
	}
 printf("\n");
// this is printing the array
 printf("-------------------------------------\n");*/

   // let threadsize be equal to n for now
   int n=0,i=0,retVal=0;
   pthread_t *thread;
   n = threadSize1; //number of threads we want
  
   
   //the number of elements in threads to run
   int threadAmount = arraySize/n; //where n is threadSize (the amount of elements in between each thing)
   //res->upperIndex = threadAmount-1;
   //res->currIndex=0;

   //before we go into loop, we do the bound calculations
	resultStruct bounds[n]; //make a result struct for each thread
	int q;   
	for(q=0; q<n; q++){
		if(q==0){
			bounds[q].upperIndex= threadAmount-1;
			bounds[q].currIndex=  0;
		}else if(q==(n-1)){
			bounds[q].upperIndex= arraySize-1;
			bounds[q].currIndex= bounds[q-1].upperIndex + 1;
		}else{
			bounds[q].currIndex= bounds[q-1].upperIndex + 1;
			bounds[q].upperIndex= bounds[q].currIndex + threadAmount -1;
		}
		bounds[q].result=-1;
		//printf("Added: upper: %d, lower: %d, %d\n", bounds[q].upperIndex, bounds[q].currIndex, bounds[q].result);
		
	}




  //now we have bounds arary
   
   thread = (pthread_t *) malloc (n*sizeof(pthread_t)); //check piazza, might be wrong
  
   for (i=0;i<n;i++){
	q=i; 
        resultStruct *res = malloc(sizeof(resultStruct)); //struct to pass args to function
	res->upperIndex=bounds[q].upperIndex;
	res->currIndex=bounds[q].currIndex;
	res->result = -1;
	//printf("Res values: %d upper, %d current, %d flag\n", res->upperIndex, res->currIndex, res->result);
	 
       retVal=pthread_create(&thread[i],NULL,threadFunction,res);

       if(retVal!=0){
           printf("Get forked. pthread_create failed in %d_th pass\n",i);
           exit(-1);        
       }
        //if(res->result !=-1){
	//	fin=res->result;
	//}
	//free(res);        
   }

   for(i=0;i<n;i++){
        retVal=pthread_join(thread[i],NULL);
            if(retVal!=0){
               printf("pthread_join failed in %d_th pass\n",i);
               exit(-1);        
            }
   }

printf("Target %d was found at array index %d\n", target, fin);
//printf("Thread count: %d\n", count);
return fin;

}


void *threadFunction (void* arg)
{
	count++;
	int itemsPerThread=0;
	  
    resultStruct *data = (resultStruct*) arg;
    /*printf("Flag is : %d\n", data->result);
    printf("Curr index: %d\n", data->currIndex);
    printf("Upper index: %d\n", data->upperIndex);  
*/  

    //int threadNum = (intptr_t)arg;

        //now search
	int k;
	
        
	//printf("Current index: %d\n", data->currIndex);
	for(k=data->currIndex; k<=data->upperIndex; k++){
		//printf("%d\n",ptr[k]);
		itemsPerThread++;
		if(ptr[k]==target){
			
			//printf("Checking if %d == %d\n", ptr[k], target);
			//printf("Found at index: %d\n",k);
                        fin=k;
			
			break;
		}
	}

	
	//pthread_exit();
	//printf("Items per thread: %d\n", itemsPerThread);
	//itemsPerThread=0;
    //need to exit the way he wants ys to
    

    //pid_t tid = syscall(SYS_gettid);

    //printf("I am in thread no : %d with Thread ID : %d\n",threadNum,/(int)tid);

}
