/*******************************************************************
 * Andrew Hogan
 * Assignment number: 1
 * Date: 10/2/2020 
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
	int i;
	int rr;
	int infile, outfile, filesize;
	char buffer[1];

	if( argc !=3 ) {
		fprintf(stderr, "USAGE: %s inputFile outputFile.\n", argv[0]);
		exit(-1);
	}


	if( (infile = open(argv[1], O_RDONLY)) == -1)	
		return(-1);

	if((outfile = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR))==-1) {
		close(infile);
		return (-2);
	}

	filesize=lseek(infile, (off_t)0, SEEK_END);

	for(i=filesize-1; i>=0; i--) {

		/* 
		 * use lseek() to move the file pointer to the ith position
		 * To set the file pointer to a position use the SEEK_SET flag
		 * in lseek().
		 */

		lseek(infile, (off_t)i-filesize, SEEK_END);

		rr = read(infile, buffer, 1);	/* read one byte */

		if( rr != 1 ) {
			fprintf(stderr, "Couldn't read 1 byte [%d]\n", rr);
			exit(-1);
		}

		rr = write(outfile, buffer, 1); /* write the byte to the file*/

		if( rr != 1 ) {
			fprintf(stderr, "Couldn't write 1 byte [%d]\n", rr);
			exit(-1);
		}
	}

	close(infile);
	close(outfile);

	return(0);
}
