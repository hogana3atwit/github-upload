#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int THREADS_PRINT = 0;	// could generate tons of output
const int USE_MUTEX     = 1;	// <<<<<<<   CHANGE THIS TO 0    >>>>>>>>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *fooUP() {
   for(int i=0; i < 10000; i++) {
   	if( USE_MUTEX ) pthread_mutex_lock( &mutex1 );
   	counter++;
   	if( THREADS_PRINT ) printf("Counter Up to: %d\n", counter);
   	if( USE_MUTEX ) pthread_mutex_unlock( &mutex1 );
   }
}

void *fooDOWN() {
   for(int i=0; i < 10000; i++) {
   	if( USE_MUTEX ) pthread_mutex_lock( &mutex1 );
   	counter--;
   	if( THREADS_PRINT ) printf("Counter Down to: %d\n", counter);
   	if( USE_MUTEX ) pthread_mutex_unlock( &mutex1 );
   }
}

int main() {
   const int NUM_THREADS = 100;	// needs to be even, see code.
   pthread_t T[NUM_THREADS];

   for( int i = 0; i < NUM_THREADS; i+=2) {
      if( pthread_create( &T[i], NULL, &fooUP, NULL) != 0 ) {
	  perror("Thread creation");
      }

      if( pthread_create( &T[i+1], NULL, &fooDOWN, NULL) != 0 ) {
	  perror("Thread creation");
      }
   }


   for( int i = 0; i < NUM_THREADS; i++) {
      pthread_join( T[i], NULL);
   }

   printf("\n\tTHE COUNTER'S VALUE IS: %d\n\n", counter);

   exit(0);
}

