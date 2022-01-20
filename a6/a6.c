/*
Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) is licensed under a Creative Commons Attribution-NonCommercial 3.0 Unported License (http://creativecommons.org/licenses/by-nc/3.0/).
*/
//
// To compile:   gcc -o a6 a6.c -lm -lpthread
//
// This program uses the STB library (http://nothings.org/)
// which points to the code at: https://github.com/nothings/stb
//
// You need to download the following two file:
//	a) stb_image.h         to load images
//	b) stb_image_write.h   to write images
//
// This library enables you to load images (png, jpg, etc).
// You can then manipulate the images at the pixel level.
// Then you can save the pixels as an image.
//
#include <stdio.h>

#include <pthread.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//
// GLOBAL VARIABLES
//

struct tStruct {
	int id;
};

pthread_mutex_t lock;
struct tStruct *myStructs;

int w,h,c;             // width, height, channels per pixel.
unsigned char *data;
int numberOfThreads;
int curRow;
int Y;


/*
 * This function will be called by all threads
 */
void *threadFunc(void *ptr) {
	/*
	 *  EXAMPLE 3:  Now let's convert our image to an 8-color one.
	 *              For each channel in RGB, set its value to 0 or to
 	 *              255 depending on its distance to these numbers.
	 *		if( channelValue > 127 )
	 *			channelValue = 255
	 *		else
	 *			channelValue = 0
	 *
	 * This algorithm produces an image with 8 colors:
	 *            RED     GREEN    BLUE
	 *             0        0        0
	 *	       0        0       255
	 *             0       255       0
	 *	       0       255      255
	 *            255       0        0
	 *            255       0       255
	 *            255      255       0
	 *            255      255      255
	 *
	 * Note that these might not be the "best" 8 colors.
	 */
	int tid = ((struct tStruct *) ptr)->id;

	printf("My id is: %d\n", tid);
	int V = (h + numberOfThreads - 1) / numberOfThreads;
	printf("Height: %d, Number of Threads %d, Rows per Thread: %d\n", h, numberOfThreads, V);

	pthread_mutex_lock(&lock);
	if(curRow + V > h) {
		for(Y = curRow; Y < h; Y++) {
        	        for(int X = 0; X < w; X++) {
				unsigned char R = data[(Y*w+X)*c + 0];
                        	unsigned char G = data[(Y*w+X)*c + 1];
                       	        unsigned char B = data[(Y*w+X)*c + 2];

                       	        R = ( R > 127 ) ? (char) 255 : (char) 0;
                    	        G = ( G > 127 ) ? (char) 255 : (char) 0;
                                B = ( B > 127 ) ? (char) 255 : (char) 0;


                               data[(Y*w+X)*c + 0] = R;
                               data[(Y*w+X)*c + 1] = G;
                               data[(Y*w+X)*c + 2] = B;
		       }
		}

	} else {
		for(Y = curRow; Y < curRow + V; Y++) {
                        for(int X = 0; X < w; X++) {
                                unsigned char R = data[(Y*w+X)*c + 0];
                                unsigned char G = data[(Y*w+X)*c + 1];
                                unsigned char B = data[(Y*w+X)*c + 2];

                                R = ( R > 127 ) ? (char) 255 : (char) 0;
                                G = ( G > 127 ) ? (char) 255 : (char) 0;
                                B = ( B > 127 ) ? (char) 255 : (char) 0;


                               data[(Y*w+X)*c + 0] = R;
                               data[(Y*w+X)*c + 1] = G;
                               data[(Y*w+X)*c + 2] = B;
                       }
                }
		curRow = Y;
	}
	pthread_mutex_unlock(&lock);
	//}
	//  **** TODO ****
	// Here you process the image.
	// Each of the   numberOfThreads    threads will process
	// at most   V   number of rows.  
	// Make sure you do not attempt to process more than   h    number of rows.



}

int main(int argc, char **argv) {

	if( argc != 4 ) {
		fprintf(stderr, "USAGE: %s <inputImageFilename> <outputImageFilename> <Number_of_Threads>\n", argv[0]);
		exit(-1);
	}

	numberOfThreads = atoi(argv[3]);
	/*
	 * here, we dynamically allocate space for the 
	 * structs we will pass to our threads.
	 */
	myStructs = (struct tStruct *) malloc(sizeof(struct tStruct) * numberOfThreads);

	pthread_t *tids = (pthread_t *) malloc(sizeof(pthread_t) * numberOfThreads);

	if(pthread_mutex_init(&lock, NULL) != 0) {
		printf("Mutex init has failed\n");
		exit(-1);
	}
	/*
	 * 1. Load the input picture.
	 */
	if( (data = stbi_load(argv[1], &w, &h, &c, 0)) == NULL ) {
		perror("Loading image.");
		exit(-1);
	}


	/*
	 * 2. Create the thread that will process the input image.
	 *    We pass an id to each thread which is a number 0...numberOfThreads
	 */
	for( int i=0; i < numberOfThreads; i++) {
		myStructs[i].id = i;
		if( pthread_create(&(tids[i]), NULL, &threadFunc, (void *) &myStructs[i]) != 0 ) {
			perror("pthread_create");
			exit(-2);
		}
	}


	/*
	 * 3. Wait for every thread to finish.
	 */

	for( int i=0; i < numberOfThreads; i++) {
		if( pthread_join(tids[i], NULL) != 0 ) {
			fprintf(stderr, "[FATAL] pthread_join() failed!\n");
		}

	}



	/*
	 * 4. Now that all threads finished processing the image,
	 *    save the the processed image to the output file name.
	 */
	if( stbi_write_png(argv[2], w, h, c, data, w*c) == 0 ) {
		perror("Writing PNG");
		exit(-1);
	}

	free(data);
	return(0);
}
