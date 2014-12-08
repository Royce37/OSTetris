#pragma once

#ifndef _tetris_h_inluded_
#define _tetris_h_inluded_
#include "Tetrimino.h"
#include "Stats.h"

class Tetris
{
	Tetris(void);
	~Tetris(void);
	
	const int ROWS = 22;
	const int COL = 10;

private:
	double baseDrp;
	int FPS;
	double drpRate;
	bool running;
	int matrix[ROWS][COL];
	Tetrimino actTet;
	List<int> tetQueue;
	double placeDelay;
	bool snapped;
	double spdPerLvl;

public:
	int dropCnt = 0;
	int delayCnt = 0;
	Stats stats;

	//update
	//This is the main method of the game logic, everything happens in here
	public bool update(int time);
	public bool init();
	public void reset();
	public void start();
	public bool pause(bool stop);
	public int checkColor(int row, int column);
	public bool isRunning();
	public void left();
	public void right();
	public void down();
	public void hardDrop();
	public void rotateRight();
	public void rotateLeft();

	private bool canSpawn();
	private void gameOver();
	private void checkQueue();
	private void createGridMatrix();
	private void clearFilled();
	private bool rowStatus(int row);
	private void clearRow(int startRow);
}

#endif