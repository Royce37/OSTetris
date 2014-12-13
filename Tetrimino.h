//#pragma once

#ifndef _tetrimino_h_inluded_
#define _tetrimino_h_inluded_

#define PIECE_SIZE 4
#define ROT_SIZE 5
#define NULL 0

#include "Tetris.h"

class Tetrimino
{

private:
	static const int pieces[7][4][PIECE_SIZE][2];
	static const int rotRight[4][5][2];
	static const int rotLeft[4][5][2];
	static const int rotRightI[4][5][2];
	static const int rotLeftI[4][5][2];
	int x, y;
	int typ, type, rot;
	bool hasSpawned;
	Tetris game;
public:
	Tetrimino(void);
	~Tetrimino(void);
	void init(int posx, int posy, int ttype, const Tetris &tgame);
	bool canDrop();
	void drop();
	bool checkLeft();
	void moveLeft();
	bool checkRight();
	void moveRight();
	const int* checkRotateRight();
	void rotateRight();
	const int* checkRotateLeft();
	void rotateLeft();
	void setActive(bool set);
	//bool isActive();
};

#endif
