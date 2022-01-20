/*******************************************************************
 * Andrew Hogan
 * Assignment number: 3
 * Date: 10/27/20
 *******************************************************************
 * Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) 
 * is licensed under a Creative Commons Attribution-NonCommercial 
 * 3.0 Unported License 
 * (http://creativecommons.org/licenses/by-nc/3.0/). 
 *******************************************************************/

#include <stdio.h>

#include <unistd.h>     // execlp (for freeBSD)
#include <stdlib.h>     // exit() (for freeBSD)


int main() {
	int pfd[2];
	int pid;
	int pfd2[2];
	int pid2;

	if (pipe(pfd) == -1) {
		perror("pipe failed");
		exit(-1);
	}
	if ((pid = fork()) < 0) {
		perror("fork failed");
		exit(-2);
	}
	if (pid == 0) {
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		if(pipe(pfd2) == -1) {
			perror("pipe failed");
			exit(-3);
		}
		if((pid2 = fork()) < 0) {
			perror("fork failed");
			exit(-4);
		}
		if(pid2 == 0) {
			close(pfd2[1]);
			dup2(pfd2[0], 0);
			close(pfd2[0]);
			execlp("wc", "wc", (char *) 0);
			perror("wc failed");
			exit(-5);
		} else {
			close(pfd2[0]);
			dup2(pfd2[1], 1);
			close(pfd2[1]);
			execlp("grep", "grep", "andrew", (char *) 0);
			perror("grep failed");
			exit(-6);
		}
		exit(-7);
	} else {
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		execlp("ps", "ps", "-ef", (char *) 0);
		perror("ps failed");
		exit(-4);
	}
	exit(0);
}
