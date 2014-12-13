#include "Tetris.h"
#include "Tetrimino.h"
#include "Stats.h"
#include <list>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace std;

Tetris::Tetris()
{
	baseDrp = .5;
	FPS = 30;
	drpRate = 1;
	running = false;
	matrix[] = null;
	placeDelay = 0;
	snapped = false;
	spdPerLvl = .05;

	dropCnt = 0;
	delayCnt = 0;
	//Set a random seed based off of time
	srand(unsigned (time(0)));
}

Tetris::~Tetris()
{
	if(actTet != NULL)
	{
		delete actTet;
	}
}

bool Tetris::update()
{
	if(running)
	{
		dropCnt++;
		if(dropCnt > drpRate)
		{
			if(actTet->isActive() == false)
			{
				if(canSpawn())
				{
					//log("creating new tetrimino");
					//actTet = new Tetrimino(4, 0, game.tetQueue.dequeue());
					actTet->init(4, 0, tetQueue.front(), *this);
					tetQueue.pop_front();
					checkQueue();
				}
				else
				{
					gameOver();
				}
			}
			else
			{
				//log(game.actTet->canDrop());
				if(actTet->canDrop())
				{
					if(delayCnt > 0)
					{
						delayCnt = 0;
					}
					actTet->drop();
				}
				else
				{
					if(delayCnt > placeDelay || snapped === true)
					{
						actTet->setActive(false);
						delayCnt = 0;
						//sfx.play();
						clearFilled();
						snapped = false;
					}
					else
					{
						delayCnt++;
					}
				}
			}
			dropCnt = 0;
		}
	}
}

bool Tetris::init()
{
	// log("Initializing game in Tetris.init");
	createGridMatrix();
	running = false;
	stat.init();
	checkQueue();
}

void Tetris::reset()
{
	running = false;
	tetQueue.erase();
	checkQueue();
	actTet->reset();
	createGridMatrix();
	stat.reset();
	//game.music.pause();
}
void Tetris::start()
{
	reset();
	//stat.start(level);
	drpRate = (baseDrp-(stat.getLevel() * spdPerLvl)) * FPS;
	running = true;
	placeDelay = 1 + (stat.getLevel() * 1.5);
	//game.music.play();
}
bool Tetris::pause()
{
	if(running == true)
	{
		running = false;
		//game.music.pause();
	}
	else if(running == false)
	{
		running = true;
	}
	//alert("Game is paused, press OK to resume");
}
int Tetris::checkColor(int row, int column)
{
	return matrix[row][column];
}
bool Tetris::isRunning()
{
	return running;
}
void Tetris::left()
{
	if(running && actTet->isActive())
	{
		//log(game.actTet->checkLeft());
		if(actTet->checkLeft())
		{
			actTet->moveLeft();
		}
	}
}
void Tetris::right()
{
	if(running && actTet->isActive())
	{
		//log(game.actTet->checkRight());
		if(actTet->checkRight())
		{
			actTet->moveRight();
		}
	}
}
void Tetris::down()
{
	if(running && actTet->isActive())
	{
		if(actTet->canDrop())
		{
			actTet->drop();
		}
	}
}
void Tetris::hardDrop()
{
	if(running && actTet->isActive())
	{
		while(actTet->canDrop())
		{
			actTet->drop();
		}
		snapped = true;
	}
}
void Tetris::rotateRight()
{
	if(running && actTet->isActive())
	{
		actTet->rotateRight();
	}
}
void Tetris::rotateLeft()
{
	if(running && actTet->isActive())
	{
		actTet->rotateLeft();
	}
}


bool Tetris::canSpawn()
{
	int i;
	for(i = 4; i < 8; i++)
	{
		if(matrix[1][i] != 0 || matrix[0][i] != 0)
		{
			return false;
		}
	}
	return true;
}

void Tetris::gameOver();
{
	running = false;
}

void Tetris::checkQueue()
{
	if(tetQueue.empty() == true || tetQueue.size < 5)
	{
		array<int,7> tempAry = {1,2,3,4,5,6,7};
		random_shuffle(tempAry.begin(), tempAry.end());
		for(int i = 0; i < 7; i++)
		{
			tetQueue.push_back(tempAry[i]);
		}
	}
}

void Tetris::createGridMatrix()
{
	int i, j;
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COL; j++)
		{
			matrix[i][j] = 0;
		}
	}
	// log("End createGameMatrix");
	// game.testCase1();
}

void Tetris::clearFilled()
{
	List<int> toClear;
	int tFilled = 1, i, k;
	int preClearLvl = stat.getLevel();
	for(i = ROWS-1; i > 0 && tFilled > 0; i--)
	{
		tFilled = rowStatus(i);
		if(tFilled == 10)
		{
			toClear.push_back(i);
		}
	}
	// log("rows to clear: "+toClear);
	//Update score
	stat.statUpdate(toClear.size());
	for(k = toClear.size()-1; k >= 0; k--)
	{
		//log("clearing row: " + toClear[k]);
		clearRow(toClear.front());
		toClear.pop_front();
	}
	if(preClearLvl < stat.getLevel())
	{
		drpRate = (baseDrp-(stat.getLevel() * spdPerLvl)) * FPS;
		placeDelay = 1 + (stat.getLevel() * 1.5);
	}
}

bool Tetris::rowStatus(int row)
{
	int tFilled = 0;
	for(int i = 0; i < COL; i++)
	{
		if(matrix[row][i] > 0)
		{
			tFilled++;
		}
	}
	return tFilled;
}

//clearRow method
//Purpose: starts at passed in row and brings all cells 
//			above that row down by 1
void Tetris::clearRow(int startRow)
{
	int iter, j;
	for(iter = startRow; iter >= 0 && rowStatus(iter) > 0; iter--)
	{
		for(j = 0; j < COL; j++)
		{
			if(iter == 0)
			{
				matrix[iter][j] = 0;
			}
			else
			{
				matrix[iter][j] = matrix[iter-1][j];
			}
		}
	}
}

void Tetris::setCoord(int row, int col, int typ)
{
	game.matrix[row][col] = typ;
}
