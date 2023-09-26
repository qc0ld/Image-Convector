#include "func.h"

void func(int w, int h, int ch, unsigned char *im, unsigned char *res) {	//Gray = (Red ∗ 0.299 + Green ∗ 0.587 + Blue ∗ 0.114)
	double redm = 0.299, greenm = 0.587, bluem = 0.114;
	int pixel_id = 0;
	for (int i = 0; i < w*h; ++i) {
		unsigned char gray = (unsigned char) ((int) (round(redm * im[pixel_id] + greenm * im[pixel_id + 1] + bluem * im[pixel_id + 2])));
		for (int k = 0; k < ch; ++k) {
			res[pixel_id + k] = gray;
		}
		pixel_id+=3;
	}
}
