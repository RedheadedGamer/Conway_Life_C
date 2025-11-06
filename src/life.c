/* W Pretorius */

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

void set_input_simulate() 
{
	struct termios new_tio;
	tcgetattr(STDIN_FILENO, &new_tio);
	new_tio.c_cc[VMIN] = 0;
	new_tio.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void set_input_edit() 
{
	struct termios new_tio;
	tcgetattr(STDIN_FILENO, &new_tio);
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


void simulate(int mode)
{
	int game = 1, paused = mode;
	int i, j;
	char c;
	double delta = 0.1;
	int nsecond = delta * 1000000000;
	struct timespec rem, req = { 0, nsecond };

	reset_gen();

	while (game) {
		if (paused) {
			printmap(3);
		} else {
			printmap(0);
		}

		c = getch();
		
		if (c == 'q') {
			game = 0;
			return;
		} else if (c == ' ') {
			if (paused) {
				set_input_simulate();
				paused = 0;
			} else {
				set_input_edit();
				paused = 1;
			}
		} else if  (paused && c == 'n') {
			sim_once();
		}

		if (!paused) {
			sim_once();
		}

		nanosleep(&req, &rem);
	}
}


int main(int argc, char *argv[])
{
	int i = 0, j = 0;
	int h = 8, w = 8;
	int posy = 0, posx = 0;
	char game = 1;
	char c;

	if (argc > 2) {
		h = atoi(argv[1]);
		w = atoi(argv[2]);
	}


	init(h, w);	

	selected(posy, posx);

	printmap(1);
	set_input_raw();

	while (game) {
		printmap(1);

		c = getch();
		if (c == 'q') {
			game = 0;
		} else if (c == 'a') {
			selected(posy, posx);
			posx--;
			
			if (posx < 0) {
				posx = w - 1;
			}
			
			selected(posy, posx);
		} else if (c == 'd') {
			selected(posy, posx);
			posx++;

			if (posx >= w) {
				posx = 0;
			}

			selected(posy, posx);
		} else if (c == 'w') {
			selected(posy, posx);
			posy--;
			
			if (posy < 0) {
				posy = h - 1;
			}
			
			selected(posy, posx);
		} else if (c == 's') {
			selected(posy, posx);
			posy++;

			if (posy >= h) {
				posy = 0;
			}

			selected(posy, posx);
		} else if (c == ' ') {
			toggle(posy, posx);
		} else if (c == 'r') {
			set_input_simulate();
			selected(posy, posx);
			simulate(0);
			set_input_edit();
			selected(posy, posx);
		} else if (c == 'n') {
			selected(posy, posx);
			simulate(1);
			set_input_edit();
			selected(posy, posx);
		} else if (c == 'c') {
			clearmap();
		}

	}

	
	selected(posy, posx);
	printmap(2);

	freeme();

	reset_input();

	return EXIT_SUCCESS;
}

/* BS&T */
