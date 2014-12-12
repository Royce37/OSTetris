//#pragma once

#ifndef _view_h_included_
#define _view_h_included_
#include "Tetris.h"
#include <curses.h>

class View
{
	View();
	~View();
public:
	void init(const Tetris &tgame);
	void update();

private:
	Tetris game;
};