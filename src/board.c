/* W Pretorius */

#include <stdio.h>
#include <stdlib.h>
#include "c_list.h"

static int **map;
static int h, w, gen;

void freeme(void)
{
	int i;

	for (i = 0; i < h; i++) {
		free(map[i]);
	}

	free(map);
}

void clearmap(void)
{
	int i, j;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			map[i][j] = 0;
		}
	}
}

int init(int y, int x)
{
	int i, j;

	h = y;
	w = x;
	map = (int **)malloc(h * sizeof(int *));

	if (map == NULL) {
		return EXIT_FAILURE;
	}

	for (i = 0; i < h; i++) {
		map[i] = (int *)malloc(w * sizeof(int));

		if (map[i] == NULL) {
			for (j = 0; j < i; j++) {
				free(map[j]);
			}

			free(map);
			return EXIT_FAILURE;
		}
	}

	clearmap();	

	return EXIT_SUCCESS;
}

void create(int y, int x)
{
	map[y][x] = 1;
}

void selected(int y, int x)
{
	if (map[y][x] > 1) {
		map[y][x] -= 2;
	} else {
		map[y][x] += 2;
	}
}

void toggle(int y, int x)
{
	switch (map[y][x]) {
		case 0:
			map[y][x] = 1;
			break;
		case 1:
			map[y][x] = 0;
			break;
		case 2:
			map[y][x] = 3;
			break;
		case 3: 
			map[y][x] = 2;
			break;

	}
}

void reset_gen(void)
{
	gen = 0;
}


void sim_once(void)
{
	int i, j, pd;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			int count = 0;

			if (i > 0) {
				count += map[i - 1][j];
			}
			if (i < h - 1) {
				count += map[i + 1][j];
			}
			if (j > 0) {
				count += map[i][j - 1];
			}
			if (j < w - 1) {
				count += map[i][j + 1];
			}
			
			if (i > 0 && j > 0) {
				count += map[i - 1][j - 1];
			}
			if (i < h - 1 && j < w - 1) {
				count += map[i + 1][j + 1];
			}
			if (j > 0 && i < h - 1) {
				count += map[i + 1][j - 1];
			}
			if (j < w - 1 && i > 0) {
				count += map[i - 1][j + 1];
			}

			if (map[i][j] % 2 == 0) {
				if (count == 3) {
					push(i, j);
				}
			} else {
				if ((count < 2) || (count > 3)) {
					push(i,j);
				}
			}
		}
	}

	while (pop(&i, &j)) {
		toggle(i,j);
	}
}


void printmap(int mode)
{
	int i, j;

	printf("\033[2J");
	printf("\033[H");
	
	if (mode == 1) {
		printf("W:↑, A:←, S:↓, D:→, Q: quit, Space: toggle, R: run, N: step\n");
	} else if (mode == 2) {
		printf("Final state: \n");
	} else if (mode == 3) {
		printf("Simulating... Q: edit, Space: run, N: next generation \n");
	} else {
		printf("Simulating... Q: edit, Space: pause \n");
	}

	printf("╔═");
	for (i = 0; i < w; i++) {
		printf("══");
	}
	printf("═╗\n");

	for (i = 0; i < h; i++) {
		
		printf("║ ");

		for (j = 0; j < w; j++) {
			if (map[i][j] == 1) {
				/* printf("⬜"); */
				printf("\x1b[7m  \x1b[0m");
			} else if (map[i][j] == 0) {
				/* printf("⬛"); */
				printf("\x1b[37m  \x1b[0m");
			} else if (map[i][j] == 3) {
				printf("\x1b[7m[]\x1b[0m");
			} else {
				printf("[]");
			}
		}
		printf(" ║\n");
	}
	
	printf("╚═");
	for (i = 0; i < w; i++) {
		printf("══");
	}

	printf("═╝\n");

	if (!mode) {
		printf("Generation: %d\n", gen);
		gen++;
	}
}

/* BS&T */
