#include "Tetris.h"
#include <curses.h>

using namespace std;

View::~View()
{
	if(game != NULL)
	{
		delete game;
	}
}

void View::init()
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	getmaxyx(stdscr, y, x);
}

void View::update()
{

}