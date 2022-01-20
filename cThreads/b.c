/* 
 * How to compile:   gcc -o executableName file.c -lpthread 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


#define MAXTHREADS 5

struct tStruct {
	int id;
	int a;
	int b;
	float c;
	char str[50];
};

struct tStruct myStruct[MAXTHREADS];



static void *doit(void *aStruct) {

	sleep(((struct tStruct *) aStruct)->id);
	char * msg = ((struct tStruct *) aStruct)->str;

	printf("I am thread number: %d  (%s)\n", ((struct tStruct *) aStruct)->id, msg);

	return(NULL);
}


int main(int argc, char **argv) {
	int i;
	pthread_t tids[MAXTHREADS];

	// pthread_setconcurrency(MAXTHREADS);

	for( i = 0; i < MAXTHREADS; i++) {

		myStruct[i].id=i;
		if( i % 2 == 0)
			strcpy(myStruct[i].str, "EVEN");
		else
			strcpy(myStruct[i].str, "ODD");

		if( pthread_create(&(tids[i]), NULL, &doit, (void *) &myStruct[i]) != 0 ) {
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
