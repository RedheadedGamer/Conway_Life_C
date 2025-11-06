#include <stdio.h>
#include <stdlib.h>

static int **map;
static int h, w;

void freeme(void)
{
	int i;

	for (i = 0; i < h; i++) {
		free(map[i]);
	}

	free(map);
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

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			map[i][j] = 0;
		}
	}

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

void printmap(void)
{
	int i, j;

	printf("\033[2J");
	printf("\033[H");
	
	printf("W:↑, A:←, S:↓, D:→, Q: quit, Space: toggle\n");
	printf(" ");
	for (i = 0; i < w; i++) {
		printf(" %d",i);
	}
	printf("\n");

	for (i = 0; i < h; i++) {
		printf("%d ",i);
		for (j = 0; j < w; j++) {
			if (map[i][j] == 1) {
				printf("■ ");
			} else if (map[i][j] == 0) {
				printf("□ ");
			} else if (map[i][j] == 3) {
				printf("◆ ");
			} else {
				printf("◇ ");
			}
		}
		printf("\n");
	}
}
