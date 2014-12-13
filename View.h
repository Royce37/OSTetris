//#pragma once

#ifndef _view_h_included_
#define _view_h_included_
#include "Tetris.h"
#include <curses.h>

#define MIN_HEIGHT (ROWS + 2)
#define MIN_WIDTH (COL + 2)
#define STAT_ROWS 4
#define STAT_COLS 8

class View
{
public:
	View();
	~View();
	void init(const Tetris &tgame);
	void update();
	int getInput();

private:
	static const int hiddenRows = 2;
	Tetris game;
	WINDOW *gameWin;
	WINDOW *scoreWin;
	WINDOW *holdWin;
	WINDOW* createWin(int rows, int cols, int ypos, int xpos);
	void colorBlock(int x, int y, WINDOW* win);
	int BLACK_COLOR, CYAN_COLOR, YELLOW_COLOR, PURPLE_COLOR, GREEN_COLOR, RED_COLOR, BLUE_COLOR, WHITE_COLOR;
};

#endif
