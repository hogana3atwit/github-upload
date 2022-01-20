/*
Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) is licensed under a Creative Commons Attribution-NonCommercial 3.0 Unported License (http://creativecommons.org/licenses/by-nc/3.0/).
*/
//
// To compile:   gcc -o t t.c -lm
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

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char **argv) {
	int w,h,c; // width, height, channels per pixel.
	unsigned char *data;

	size_t size = sizeof(data)/sizeof(int);
        printf("%ld\n", size);

	if( argc != 2 ) {
		fprintf(stderr, "USAGE: %s <imageFilename>\n", argv[0]);
		exit(-1);
	}


	/*
	 *  EXAMPLE 1:  Load an image, then save it as png and jpg
	 */

	if( (data = stbi_load(argv[1], &w, &h, &c, 0)) == NULL ) {
		perror("Loading image.");
		exit(-1);
	}
	printf("%d x %d (%d bytes per pixel)\n", w, h, c);

	if( stbi_write_png("OUT.png", w, h, c, data, w*c) == 0 ) {
		perror("Writing PNG");
		exit(-1);
	}
 	if( stbi_write_jpg("OUT.jpg", w, h, c, data, 80) == 0 ) {
		perror("Writing PNG");
		exit(-1);
	}


	free(data);


	/*
	 *  EXAMPLE 2a:  Load an image and force it to be 
	 *              4 channels  (RGBA)
	 *              Then save the resulting image as png
	 *              which does support the alpha channel.
	 */
	if( (data = stbi_load(argv[1], &w, &h, &c, 4)) == NULL ) {
		perror("Loading image.");
		exit(-1);
	}
	if( stbi_write_png("OUT_rgba.png", w, h, 4, data, w*4) == 0 ) {
		perror("Writing PNG");
		exit(-1);
	}

	/*
	 *  EXAMPLE 2b:  Swap the red and blue channels. 
	 *               Then save it as a png image.
	 */
	for(int Y = 0; Y < h; Y++) {
		for(int X = 0; X < w; X++) {
			char red   = data[(Y*w+X)*4 + 0];
			char blue  = data[(Y*w+X)*4 + 2];

			data[(Y*w+X)*4 + 0] = blue;
			data[(Y*w+X)*4 + 2] = red;
		}
	}
	if( stbi_write_png("OUT_rgba_MODIFIED.png", w, h, 4, data, w*4) == 0 ) {
		perror("Writing PNG");
		exit(-1);
	}

	free(data);

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

	if( (data = stbi_load(argv[1], &w, &h, &c, 0)) == NULL ) {
		perror("Loading image.");
		exit(-1);
	}
	for(int Y = 0; Y < h; Y++) {
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


	if( stbi_write_png("OUT_nearestCollors.png", w, h, c, data, w*c) == 0 ) {
		perror("Writing PNG");
		exit(-1);
	}
}
