#include "Tetris.h"
#include "View.h"
#include <curses.h>

using namespace std;

View::View()
{
}

View::~View()
{
}

void View::init(const Tetris &tgame)
{
	game = tgame;
	printf("test\n");
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	//nodelay(stdscr, TRUE);
	
	int x,y;
	getmaxyx(stdscr, y, x);
	if(x < MIN_WIDTH || y < MIN_HEIGHT)
	{
		endwin();
		printf("Screen too small\n");
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
			int color;
			switch(game.matrix[i][j])
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
				wattron(gameWin, COLOR_PAIR(color));
			}
			mvwprintw(gameWin, i + 1, j * 2 + 1, "  ");
			if(color != 0)
			{
				wattroff(gameWin, COLOR_PAIR(color));
			}
			//colorBlock(j, i, gameWin);
		}
	}
}

WINDOW* View::createWin(int rows, int cols, int ypos, int xpos)
{
	WINDOW *win;
	win = newwin(rows, cols, ypos, xpos);
	refresh();
	box(win, 0, 0);
	wrefresh(win);
	return win;
}

void View::colorBlock(int x, int y, WINDOW* win)
{
	int color;
	switch(game.matrix[x][y])
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
	int ch, status = 0;
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
				case 's':
					if(game.isRunning == false)
					{
						game.start();
					}
					break;
			}
    }
	//flushBuffer();
	return status;
}
