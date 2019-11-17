#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>


void *threadFunction (void *);

int main (void)
{

   int n=0,i=0,retVal=0;
   pthread_t *thread;

   printf("Enter the number for threads you want to create between 1 to 100 \n");
   scanf("%d",&n);

   thread = (pthread_t *) malloc (n*sizeof(pthread_t));

   for (i=0;i<n;i++){
       retVal=pthread_create(&thread[i],NULL,threadFunction,(void *)(intptr_t)i);
       if(retVal!=0){
           printf("pthread_create failed in %d_th pass\n",i);
           exit(EXIT_FAILURE);        
       }
   }

   for(i=0;i<n;i++){
        retVal=pthread_join(thread[i],NULL);
            if(retVal!=0){
               printf("pthread_join failed in %d_th pass\n",i);
               exit(EXIT_FAILURE);        
            }
   }

}

void *threadFunction (void *arg)
{
    int threadNum = (intptr_t)arg;

    pid_t tid = syscall(SYS_gettid);

    printf("I am in thread no : %d with Thread ID : %d\n",threadNum,(int)tid);


}
