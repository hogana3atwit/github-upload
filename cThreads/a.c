/* 
 * How to compile:   gcc -o executableName file.c -lpthread 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


#define MAXTHREADS 5

static void *doit(void *ptr) {

	sleep(1);

	printf("I am a thread\n");

	return(NULL);
}


int main(int argc, char **argv) {
	int i;
	pthread_t tids[MAXTHREADS];

	for( i = 0; i < MAXTHREADS; i++) {

		if( pthread_create(&(tids[i]), NULL, &doit, NULL ) ) {
			perror("pthread_create");
			exit(-2);
		}
	}
	/* 
	 * Join Threads 
	 */
	for(i = 0; i < MAXTHREADS; i++) {
		if( pthread_join(tids[i], NULL) != 0 ) {
			fprintf(stderr, "[FATAL] pthread_join() failed!\n");
		}
	}
	printf("All Threads are finished!\n");
	exit(0);
}
