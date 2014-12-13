//#pragma once

#ifndef _tetrimino_h_inluded_
#define _tetrimino_h_inluded_

#define PIECE_SIZE 4
#define ROT_SIZE 5

#include "Tetris.h"

class Tetris;

class Tetrimino
{
	Tetrimino(void);
	~Tetrimino(void);

private:
	static const int pieces[7][4][PIECE_SIZE];
	static const int rotRight[4][4];
	static const int rotLeft[4][4];
	static const int rotRightI[4][4];
	static const int rotLeftI[4][4];
	int x, y;
	int typ, rot;
	bool hasSpawned;
	Tetris game;
public:
	void init(int posx, int posy, int ttype, const Tetris &tgame);
	bool canDrop();
	void drop();
	bool checkLeft();
	void moveLeft();
	bool checkRight();
	void moveRight();
	bool checkRotateRight();
	void rotateRight();
	bool checkRotateLeft();
	void rotateLeft();
	void setActive(bool set);
	bool isActive();
};

#endif
