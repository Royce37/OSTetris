//#pragma once

#ifndef _tetris_h_inluded_
#define _tetris_h_inluded_
#include "Stats.h"
#include "Tetrimino.h"
#include <list>

#define ROWS 22
#define COL 10

class Tetrimino;

class Tetris
{
private:
	double baseDrp;
	int FPS;
	double drpRate;
	bool running;
	Tetrimino actTet;
	std::list<int> tetQueue;
	double placeDelay;
	bool snapped;
	double spdPerLvl;
	
	bool canSpawn();
	void gameOver();
	void checkQueue();
	void createGridMatrix();
	void clearFilled();
	bool rowStatus(int row);
	void clearRow(int startRow);

public:
	Tetris();
	~Tetris();
	
	int dropCnt;
	int delayCnt;
	Stats stats;
	int matrix[ROWS][COL];

	//update
	//This is the main method of the game logic, everything happens in here
	bool update();
	bool init();
	void reset();
	void start();
	bool pause();
	int checkColor(int row, int column);
	bool isRunning();
	void left();
	void right();
	void down();
	void hardDrop();
	void rotateRight();
	void rotateLeft();
	void setCoord(int row, int col, int typ);
};

#endif
