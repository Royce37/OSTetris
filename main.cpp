#include "Tetris.h"
#include "View.h"
#include <iostream>
#include <time.h>			// GetTickCount
#include <curses.h>

using namespace std;

unsigned long GetTickCount();

main()
{
	const int FRAMES_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

    DWORD next_game_tick = GetTickCount();

	Tetris game;
	game.init();
	View view;
	view.init(&game);

    int sleep_time = 0;

    bool game_is_running = true;

    while( game_is_running ) 
	{
        game.update();
        view.update();

        next_game_tick += SKIP_TICKS;
        sleep_time = next_game_tick - GetTickCount();
        if( sleep_time >= 0 ) 
		{
            Sleep( sleep_time );
        }
        else 
		{
        }
    }
}

 unsigned long GetTickCount()
{
	//Would prefer clock_gettime but don't want to do the maths right now..
	struct timeval tv;
	if( gettimeofday(&tv, NULL) != 0 )
		return 0;

	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}