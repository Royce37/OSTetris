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
	//nodelay(stdscr, TRUE);

	getmaxyx(stdscr, y, x);
	if(x < MIN_WIDTH || y < MIN_HEIGHT)
	{
		endwin();
		return;
	}

	start_color();

	//Set up color ints
	init_pair(BLACK_COLOR, COLOR_WHITE, COLOR_BLACK);		//background
	init_pair(CYAN_COLOR, COLOR_WHITE, COLOR_CYAN);			//I
	init_pair(YELLOW_COLOR, COLOR_WHITE, COLOR_YELLOW);		//O
	init_pair(PURPLE_COLOR, COLOR_WHITE, COLOR_MAGENTA);	//T
	init_pair(GREEN_COLOR, COLOR_WHITE, COLOR_GREEN);		//S
	init_pair(RED_COLOR, COLOR_WHITE, COLOR_RED);			//Z
	init_pair(BLUE_COLOR, COLOR_WHITE, COLOR_BLUE);			//J
	init_pair(WHITE_COLOR, COLOR_WHITE, COLOR_WHITE);		//L

	gameWin = createWin((ROWS - hiddenRows), COL, 1, 1);
}

void View::update()
{
	int i, j;
	for(i = hiddenRows; i < ROWS; i++)
	{
		for(j = 0; j < COL; j++)
		{
			colorBlock(j, i, 
		}
	}
}

void View::createWin(const int rows, const int cols, const int ypos, const int xpos)
{
	WINDOW *win;
	win = newwin(rows, cols, ypos, xpos);
	refresh();
	box(win, 0, 0);
	refresh_win(win);
	return win;
}

void View::colorBlock(const int x, const int y, WINDOW* win)
{
	int color;
	switch(brick_type)
	{
		case 1:
			color = CYAN_COLOR;
			break;
		case 2:
			color = YELLOW_COLOR;
			break;
		case 3:
			color = PURPLE_COLOR;
			break;
		case 4:
			color = GREEN_COLOR;
			break;
		case 5:
			color = RED_COLOR;
			break;
		case 6:
			color = BLUE_COLOR;
			break;
		case 7:
			color = WHITE_COLOR;
			break;
		default:
			color = 0;
			break;
	}
	if(color != 0)
	{
		wattron(win, COLOR_PAIR(color));
	}
	mvwprintw(win, y + 1, x * 2 + 1, "  ");
	if(color != 0)
	{
		wattroff(win, COLOR_PAIR(color));
	}
}

int View::getInput()
{
	int ch, status;
	//nodelay(stdscr, TRUE);
    if ((ch = getch()) != ERR) 
	{
        switch(ch)
			{
				//Move Down
				case KEY_DOWN:
					game.down();
					break;
				//Rotate Right
				case 'x':
				case KEY_UP:
					game.rotateRight();
					break;
				//Move Right
				case KEY_RIGHT:
					game.right();
					break;
				//Rotate Left
				case 'z':
					game.rotateLeft();
					break;
				//Move Left
				case KEY_LEFT:
					game.left();
					break;
				//Snap Down
				case ' ':
					game.hardDrop();
					break;
				//Pause
				case 'p':
					status = 1;
					break;
				//Quit
				case 'q':
					status = 2;
					break;
			}
    }
	//flushBuffer();
	return status;
}