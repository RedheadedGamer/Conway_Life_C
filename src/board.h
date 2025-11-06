#ifndef BOARD_H
#define BOARD_H

int init(int y, int x);
void create(int x, int y);
void printmap(void);
void freeme(void);
void selected(int y, int x);
void toggle(int y, int x);

#endif
