/* simple eink test */
#include <stdio.h>
#include <stdint.h>

#include <sys/time.h>

#include "ifusb_host.h"
#include "eink.h"


#include "testcover4.h"
char cmap[4] = {2, 1, 0, 3};

//#include "testepub2.h"
//char cmap[4] = {3,1,0,2};

//#include "mire.h"
//char cmap[4] = {0,1,2,3};

double get_time()
{
	struct timeval t;
	struct timezone tzp;
	gettimeofday(&t, &tzp);
	return t.tv_sec + t.tv_usec * 1e-6;
}

int main() {
	int i, j, k, cur_cmd = 0;
	double t1, t2;
	uint8_t cmd[8];
	uint8_t recv[8];


	if (!ifusb_init())
		goto out;

	eink_init();

printf("initiated.\n");
//	usleep(100000);

srand (time(NULL));

	for (i = 0; i < 4; i++) {
		cmd[i] = 0x00;
	}

printf("clear\n");
	eink_clear();
printf("cleared\n");
//sleep(2);
	// image to buf
	uint8_t img_buf[120000];
	int img_pos;

for(k=0;k<40;k++) {
	printf("TEST %d\n",k);

//sleep(1);
/*
 img_pos = 0;

	for (i = 0; i < 600; i++) {
		for (j = 0; j < 800; j += 4) {
			unsigned char pixel = 0;
			
			img_buf[img_pos] = (rand()%3)*0xAA;
			img_pos++;
		}
	}

	t1 = get_time();
	eink_draw(img_buf);
	t2 = get_time();
	printf("DRAW in %f\n", t2 - t1);
*/
	img_pos=0;
	for (i = 0; i < 600; i++) {
		for (j = 0; j < 800; j += 4) {
			unsigned char pixel = 0;
			if (i < width && (j + 3) < height) {
				int p;
				for (p = 0; p < 4; p++) {
					unsigned char dp = header_data[(height - (j + p)) * width + i];
					pixel |= (cmap[dp]) << ((3 - p) * 2);
				}

			} else {
				pixel = WHITE_4;
			}
			img_buf[img_pos] = pixel;
			img_pos++;
		}
	}

	eink_draw(img_buf);
//sleep(1);
}

/*	sleep(1);
	eink_clear();
*/
/*	sleep(1);
	eink_draw(img_buf);
*/
	sleep(3);

	eink_exit();
out:
	ifusb_close();


}