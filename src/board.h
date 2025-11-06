#ifndef BOARD_H
#define BOARD_H

int init(int y, int x);
void clearmap(void);
void printmap(int mode);
void freeme(void);
void selected(int y, int x);
void toggle(int y, int x);
void reset_gen(void);
void sim_once(void);

#endif
