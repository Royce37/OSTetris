#include "Tetris.h"
#include <curses.h>

using namespace std;

void View::init()
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
}