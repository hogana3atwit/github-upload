#include <stdio.h>
int main(int argc, char**argv) {
	int h = 3;
	int w = 5;

	for(int Y = 0; Y < h; Y++) {
		for(int X = 0; X < w; X++) {
			printf("%d\n", X);
		}
	}
}
