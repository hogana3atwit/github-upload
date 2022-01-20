#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

void *f1();
void *f2();
int  c = 0;

#define LIMIT  20

int main() {
   pthread_t t1, t2;

   pthread_create(&t1, NULL, &f1, NULL);
   pthread_create(&t2, NULL, &f2, NULL);
   pthread_join(t1, NULL);
   pthread_join(t2, NULL);

   exit(0);
}

/* 
 * Could be used to synchronize threads, such as to always have 
 * thread 2 run first, for example.
 *
 * Look at the (c == 0) part.  
 *     Could be interpreted as: If it is not my turn, let the other thread run first. 
 */
void *f1() {
   for(;;) {
      pthread_mutex_lock( &condition_mutex );
      while( (c >= 5 && c <= 7) || c == 0 ) {
         printf("\tf1() going to *** WAIT ***\n");
	 /* 
	  * This thread will be blocked until another thread signals the condition mutex.
	  *
	  * Blocked means that even though we aquired the condition_mutex, we voluntarily 
 	  * release it and then we block - get suspended; that's what the 
	  * pthread_cond_wait() does.
	  *
	  * When another thread signals the condition with: pthread_cond_signal( &condition_cond )
	  * we get woken up, re-aquire the mutex and continue running.
	  */
         pthread_cond_wait( &condition_cond, &condition_mutex );
      }
      pthread_mutex_unlock( &condition_mutex );

      pthread_mutex_lock( &count_mutex );
      c++;
      printf("Counter value f1(): %d\n", c);
      pthread_mutex_unlock( &count_mutex );

      if(c >= LIMIT) return(NULL);
    }
}

/* signals any waiting thread if any */
void *f2() {
   for(;;) {
      pthread_mutex_lock( &condition_mutex );
      if( c < 5 || c > 7 ) {
         printf("\tf2() going to signal\n");
         pthread_cond_signal( &condition_cond );	
      }
      pthread_mutex_unlock( &condition_mutex );

      pthread_mutex_lock( &count_mutex );
      c++;
      printf("Counter value f2(): %d\n", c);
      pthread_mutex_unlock( &count_mutex );

      if(c >= LIMIT) return(NULL);
   }
}

