#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include "board.h"

struct termios old_tio;


void set_input_raw() {
	struct termios new_tio;

	tcgetattr(STDIN_FILENO, &old_tio);

	new_tio = old_tio;

	new_tio.c_lflag &= ~(ICANON | ECHO);
	new_tio.c_cc[VMIN] = 1;
	new_tio.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}


void reset_input() {
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}


int getch() {
	char c;
	if (read(STDIN_FILENO, &c, 1) == -1) {
		return 0;
	}
	return c;
}


int main(int argc, char *argv[])
{
	int i = 0, j = 0;
	int h = 8, w = 8;
	int posy = 0, posx = 0;
	char game = 1;
	char c;
	double delta = 0.1;
	int nsecond = delta * 1000000000;
	struct timespec rem, req = { 0, nsecond };

	init(h, w);	

	selected(posy, posx);

	printmap();
	set_input_raw();

	while (game) {
		printmap();

		c = getch();
		if (c == 'q') {
			game = 0;
		} else if (c == 'a') {
			selected(posy, posx);
			posx--;
			
			if (posx < 0) {
				posx = 0;
			}
			
			selected(posy, posx);
		} else if (c == 'd') {
			selected(posy, posx);
			posx++;

			if (posx > w) {
				posx = w;
			}

			selected(posy, posx);
		} else if (c == 'w') {
			selected(posy, posx);
			posy--;
			
			if (posy < 0) {
				posy = 0;
			}
			
			selected(posy, posx);
		} else if (c == 's') {
			selected(posy, posx);
			posy++;

			if (posy > w) {
				posy = w;
			}

			selected(posy, posx);
		} else if (c == ' ') {
			toggle(posy, posx);
		}

	}

	
	selected(posy, posx);
	printmap();

	freeme();

	reset_input();

	printf("Hello, World\n");

	return EXIT_SUCCESS;
}
