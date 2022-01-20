#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* threadFunc(void *parameter) {
    sleep(2);
    printf("In threadFunc! %d\n", getpid());
}

int main() {
	pthread_t tid;
    	//pthread_attr_t attr;

    	pid_t pid;

	printf("\n");

    	pid = fork();

    	if(pid == 0){
        	fork();
        	pthread_create(&tid, NULL, threadFunc, NULL);
    	}
    	fork();


	printf("I AM DONE %d\n", getpid());
	pthread_exit(NULL);
}

