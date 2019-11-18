#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

//int threadCount=0;
int count=0;
int*ptr;
int target=-1;

typedef struct resultStruct{
	int currIndex;
	int upperIndex; // 
	//int* arr; //original array to be passed
	int result; //flag
	//int target; //target to be searched for
        
}resultStruct;

void *threadFunction (void *); // this will be the search function

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

int main (void)
{

   int arraySize = 10;
   target = 2; //user specified
   int numbers[arraySize];
   makeAndScramble(numbers,arraySize);
   
   printf("PRINTING ORIGINAL ARRAY\n");
   resultStruct *res = malloc(sizeof(resultStruct)); //struct to pass args to function
/*res.arr = (int*)malloc(sizeof(int)*arraySize);
if(res.arr== NULL){
	printf("Malloc won't let you. Meh.\n");
	return -1;
}*/

printf("-------------------------------------\n");
   int d=0;
   ptr=&(numbers[0]);
   	for(d=0; d<arraySize; d++){
		printf("%d\t",ptr[d]);
		//res.arr[d]=numbers[d];
		//printf("%d\t",res.arr[d]); -- values have been copied
	}
   printf("\n");
 //this is printing the array
 printf("-------------------------------------\n");

res->result=-1;
int fin=0;
   // let threadsize be equal to n for now
   int n=0,i=0,retVal=0;
   pthread_t *thread;

   /*printf("Enter the number for threads you want to create between 1 to 10 \n");*/

   n = 2; //number of threads we want
   //scanf("%d",&n); 
   //user enters thread size, for now it will be from stdin
   
   //the number of threads to run
   int threadAmount = arraySize/n; //where n is threadSize (the amount of elements in between each thing)
   //int currIndex = 0;
   //int upperIndex = threadAmount-1;
  /* res.upperIndex = upperIndex;
   res.currIndex= currIndex;*/ //use this if struct

   res->upperIndex = threadAmount-1;
   res->currIndex=0;
   //low = currIndex;
   //res.arr=numbers;
   //res.result=-1;
   //res.target=target;

   //int foundIndex=-1;
   
   //struct works

  // printf("Values in the struct: %d, %d, %d, %d\n", res.currIndex, res.upperIndex, res.arr[1], res.result); 
   
   thread = (pthread_t *) malloc (n*sizeof(pthread_t)); //check piazza, might be wrong
   
   for (i=0;i<n;i++){
       if(i==n-1){
		
          res->upperIndex = arraySize-1;
       }
       printf("\n");
       
      
       //printf("%d\n",i);
	printf("Upper bound : %d\t, Lower Bound: %d\t",res->upperIndex, res->currIndex);
       printf("\n");

	//bounds are clearly correct
	
       //retVal=pthread_create(&thread[i],NULL,threadFunction,&res);
	retVal=pthread_create(&thread[i],NULL,threadFunction,res);
//intptr_t)i); //need to fix this to reflect what is being passed in fx
       if(retVal!=0){
           printf("Get forked. pthread_create failed in %d_th pass\n",i);
           exit(EXIT_FAILURE);        
       }
        if(res->result !=-1){
		fin=res->result;
		//means we found it
		res->result=-1; //for next thread
	}
	//update struct current index after each thread is created    
	//check result --> if result is not -1, then we found it here
        //and we must reset flag
	
      
	
        	res->currIndex = res->upperIndex+1;
		res->upperIndex = res->currIndex + threadAmount - 1;
        
   }

   for(i=0;i<n;i++){
        retVal=pthread_join(thread[i],NULL);
            if(retVal!=0){
               printf("pthread_join failed in %d_th pass\n",i);
               exit(EXIT_FAILURE);        
            }
   }

}


void *threadFunction (void* arg)
{
    count++;
   
    //threadCount++;
    //printf("Thread number: %d \n", threadCount);
    resultStruct *data = (resultStruct*) arg;
    printf("Flag is : %d\n", data->result);
    printf("Curr index: %d\n", data->currIndex);
    printf("Upper index: %d\n", data->upperIndex);
return;
    
    //printf("lower: %d\n",data->currIndex);
    //printf("upper: %d\n",data->upperIndex);
    //printf("\n");
    //where *arg is the struct
    //int curr = data->currIndex;
    //int upper = data->upperIndex;
    //int* arr = arg->arr;
    //int result = arg->result;
    //data->result=4;
   // printf("On thread %d: Upper bound: %d, Lower bound: %d\n", count,data->upperIndex, data->currIndex);
printf("\n");
    //int threadNum = (intptr_t)arg;

    //now search
	int k;
        
        /*printf("Check number in range:\n");
	for(k=0;k<10; k++){
		printf("%d\t", ptr[k]);
	}	ARRAY IS BEING PRINTED CORRECTLY
	printf("\n");
	//int t1 = data->currIndex;
	//int t2 = data->upperIndex;
        //int t3 = data->target; //make this a definition
*/
	printf("Current index: %d\n", data->currIndex);
	for(k=data->currIndex; k<=data->upperIndex; k++){
		printf("%d\n",ptr[k]);
		
		if(ptr[k]==target){
			printf("Checking if %d == %d\n", ptr[k], target);
			printf("Found at index: %d\n",k);
                        data->result=k;
			break;
		}
	}
    

    //pid_t tid = syscall(SYS_gettid);

    //printf("I am in thread no : %d with Thread ID : %d\n",threadNum,/(int)tid);

}
