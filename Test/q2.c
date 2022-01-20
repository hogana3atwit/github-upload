#include <stdio.h>

#include <unistd.h>     // execlp (for freeBSD)
#include <stdlib.h>  
int main() {
        int a;
        printf("HELP\n");
        execlp("ls", "ls", (char *) 0);
	execlp("ls", "ls", (char *) 0);
        printf("HELLO WORLD\n");
        return(0);
}

