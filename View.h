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
	WINDOW* createWin(const int rows, const int cols, const int ypos, const int xpos);
	void colorBlock(const int x, const int y, WINDOW* win);
};

#endif
