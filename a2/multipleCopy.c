/*******************************************************************
 * Andrew Hogan
 * Assignment number: 2
 * Date: 10/5/2020 
 *******************************************************************
 * Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) 
 * is licensed under a Creative Commons Attribution-NonCommercial 
 * 3.0 Unported License 
 * (http://creativecommons.org/licenses/by-nc/3.0/). 
 *******************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>


int main ( int argc, char *argv[]) {
        char buffer[257];
        int rr;
        int infile, directory;
	char dout[512];

	for(int i = 1; i < argc - 1; i++) {
	 sprintf(dout, "%s/%s", argv[argc-1], argv[i]);

         if( (infile = open(argv[i], O_RDONLY)) == -1) { 
                perror("INPUT FILE");
                exit(-1);
        }



        if((directory = open(dout, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR))==-1) {
                perror("DIRECTORY FILE");
		close(infile);
                exit(-1);
        }


        /* 
         *      1) START A LOOP
         *      2) Read from input file into the buffer
         *         Don't read one byte at a time!  Try to read 257 bytes at a time. (this is a major requirement for this assignment).
         *      3) Write, whatever you read into the buffer, into the output file
         */ 
	rr = 10;
	 while(!(rr == 0)) {
                rr = read(infile, buffer, 257);
                write(directory, buffer, rr);
            }

        close(infile);
	close(directory);
}
        return(0);
}

