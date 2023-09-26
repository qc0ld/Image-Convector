#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "func.h"

void print_time(struct timespec* dur) {
	printf("%ld.", dur->tv_sec);
	char* nanos = malloc(10);
	int pos = 8;
	nanos[9] = '\0';
	int nsec = dur->tv_nsec;
	while (pos >= 0) {
		char numb = '0' + nsec % 10;
		nsec /= 10;
		nanos[pos] = numb;
		--pos;
	}
	printf("%s   ", nanos);
	free(nanos);
}

void measuret(void func(int, int, int, unsigned char*, unsigned char*), int width, int height, int channels, unsigned char* img, unsigned char* res) {
    struct  timespec beg, end, dur;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &beg);
	
	func(width, height, channels, img, res);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	
	dur.tv_sec = end.tv_sec - beg.tv_sec;
	if (end.tv_nsec < beg.tv_nsec) {
		dur.tv_sec--;
		dur.tv_nsec = 1000000000 + end.tv_nsec - beg.tv_nsec;
	} else {
		dur.tv_nsec = end.tv_nsec - beg.tv_nsec;
	}
	print_time(&dur);
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Use %s in1.bmp out1.bmp out1asm.bmp\n", argv[0]);
		return 1;
	}

    
	int width, height, channels;
	unsigned char* img = stbi_load(argv[1], &width, &height, &channels, 0);
	if (img == NULL) {
		printf("Error loading image\n");
		return 0;
	}
    if (channels < 3) {
        printf("Error in color scheme of image\n");
        return 0;
    }
	unsigned char* res = malloc(width * height * channels);
	unsigned char* res2 = malloc(width * height * channels);
	measuret(func, width, height, channels, img, res);
	measuret(funcasm, width, height, channels, img, res2);
	stbi_write_bmp(argv[2], width, height, channels, res);
	stbi_write_bmp(argv[3], width, height, channels, res2);
	stbi_image_free(res);
	stbi_image_free(res2);
}
