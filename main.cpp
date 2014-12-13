#include "Tetris.h"
#include "View.h"
#include <iostream>
#include <sys/time.h>			// GetTickCount
#include <curses.h>

using namespace std;

unsigned long GetTickCount();

int main()
{
	const int FRAMES_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	const int MAX_FRAMESKIP = 10;

    unsigned long next_game_tick = GetTickCount();
	int loops = 0;

	Tetris game;
	printf("Game initializing\n");
	game.init();
	
	printf("Game initialized\n");
	View view;
	view.init(game);

    //int sleep_time = 0;
	int quit = 0;

    bool game_is_running = true;
    while( game_is_running ) 
	{
		while( GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) 
		{
			quit = view.getInput();
			next_game_tick += SKIP_TICKS;
			loops++;
		}
		if(quit == 1)
		{
			game.pause();
			quit = 0;
		}
		else if(quit == 2)
		{
			game_is_running = false;
			quit = 0;
		}
		game.update();
        view.update();
    }
	return 0;
}

 unsigned long GetTickCount()
{
	//Would prefer clock_gettime but don't want to do the maths right now..
	struct timeval tv;
	if( gettimeofday(&tv, NULL) != 0 )
		return 0;

	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
