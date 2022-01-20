
/*******************************************************************
 * Andrew Hogan
 * Assignment number: 4
 * Date: 11/5/2020 
 *******************************************************************
 * Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) 
 * is licensed under a Creative Commons Attribution-NonCommercial 
 * 3.0 Unported License 
 * (http://creativecommons.org/licenses/by-nc/3.0/). 
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {

        int pid;
	int pfd_A[2];
	int pfd_B[2];
	int r;
        char buf[101];

	if (pipe(pfd_A) == -1) {
		perror("pipe failed");
		exit(-1);
	}

	if(pipe(pfd_B) == -1) {
		perror("pipe failed");
		exit (-2);
	}

	if((pid = fork()) < 0) {
		perror("fork failed");
		exit(-3);
	} 

        if (pid == 0 ) {
		dup2(pfd_A[0], 0);   // duplicate file descriptor 0 to point to FIRST pipe
		close(pfd_A[0]);	// CLOSE ends of FIRST pipe you don't need anymore

		dup2(pfd_B[1], 1);	// duplicate file descriptor 1 to point to SECOND pipe
		close(pfd_B[1]);	// CLOSE ends of SECOND pipe you don't need anymore

                execlp("./A4_CHILD", "./A4_CHILD", (char *) 0);
                perror("execlp");
                exit(-4);
        } 

	// PARENT PROCESS COMES HERE

        close(pfd_A[0]);
        close(pfd_B[1]);
	printf("\t*** Welcome to this number-guessing game! ***\n\n");
        while( 1 ) {
        	char NUM[100];

                printf("Enter a Number: ");
                fflush(stdout);
                scanf("%s", NUM);

		// SEND   NUM   to Child process
		write(pfd_A[1], NUM, strlen(NUM));

		// READ FROM CHILD THE RESPONSE into the variable buf and
		//      store the return value from read() into the variable r
		r = read(pfd_B[0], buf, 100);
		if( r > 0 ) {
                        buf[r] = '\0';
                        printf("%s\n", buf);
                        fflush(stdout);
                }
                else {
                        printf("[PARENT] Reading from child: read() returned %d\n", r);
                        break;
                }
        }

        return(0);
}
