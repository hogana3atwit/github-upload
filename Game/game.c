#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main() {
	int p;
	int i;
	int count;

	printf("A\n");
	if((p = fork()) < 0) {
		perror("fork failed");
		exit(-1);
	}
	if( p == 0) {
		printf("A\n");
		printf("A\n");
		fork();
		printf("A\n");
		fork();
	}
	else {
		for(i = 0; i < 2; i++) {
			printf("A\n");
			fork();
			fork();
			printf("A\n");
		}
		printf("A\n");
		fork();
	}
	printf("A\n");
	fork();
	printf("A\n");
	exit(0);
}
