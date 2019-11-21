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


int search (int arraySize, int n, int target, int * numbers)
{

	
   ptr=numbers;


   // let threadsize be equal to n for now
   int i=0,retVal=0;
   pthread_t *thread;
   //n = threadSize1; //number of threads we want
  
   
   //the number of elements in threads to run
   int threadAmount = arraySize/n; //where n is threadSize (the amount of elements in between each thing)
 	printf("-thread\n");
	printf("Array size: %d, Number of threads: %d, Target: %d\n", arraySize, n, target);

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
		
		
	}




  //now we have bounds arary
   
   thread = (pthread_t *) malloc (n*sizeof(pthread_t)); 
  
   for (i=0;i<n;i++){
	q=i; 
        resultStruct *res = malloc(sizeof(resultStruct)); //struct to pass args to function
	res->upperIndex=bounds[q].upperIndex;
	res->currIndex=bounds[q].currIndex;
	res->result = -1;

	//printf("items per thread: %d and %d\n", bounds[q].upperIndex, bounds[q].currIndex);
	count++;
	
	 
       retVal=pthread_create(&thread[i],NULL,threadFunction,res);

       if(retVal!=0){
           printf("Get forked. pthread_create failed in %d_th pass\n",i);
           exit(-1);        
       }       
   }

   for(i=0;i<n;i++){
        retVal=pthread_join(thread[i],NULL);
            if(retVal!=0){
               printf("pthread_join failed in %d_th pass\n",i);
               exit(-1);        
            }
   }

//printf("Target %d was found at array index %d\n", target, fin);
//printf("Thread count: %d\n", count);
return fin;

}


void *threadFunction (void* arg)
{
	//count++;
	
	  
    resultStruct *data = (resultStruct*) arg;

        //now search
	int k;
	
        
	//printf("Current index: %d\n", data->currIndex);
	for(k=data->currIndex; k<=data->upperIndex; k++){
		//printf("%d\n",ptr[k]);
		//itemsPerThread++;
		if(ptr[k]==target){
                        fin=k;
			
			return;
		}
	}

}
