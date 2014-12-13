//#pragma once

#ifndef _tetrimino_h_inluded_
#define _tetrimino_h_inluded_

#define PIECE_SIZE 4
#define ROT_SIZE 5

class Tetris;

class Tetrimino
{
	Tetrimino(void);
	~Tetrimino(void);

private:
	const int pieces[][][] = {
								{//I block
									{{0,1},{1,1},{2,1},{3,1}}, {{2,0},{2,1},{2,2},{2,3}}, {{0,2},{1,2},{2,2},{3,2}}, {{1,0},{1,1},{1,2},{1,3}}
								},
								{//O block
									{{0,0},{1,0},{0,1},{1,1}}, {{0,0},{1,0},{0,1},{1,1}}, {{0,0},{1,0},{0,1},{1,1}}, {{0,0},{1,0},{0,1},{1,1}}
								},
								{//T block
									{{1,0},{0,1},{1,1},{2,1}},{{1,0},{1,1},{2,1},{1,2}},{{0,1},{1,1},{2,1},{1,2}},{{1,0},{0,1},{1,1},{1,2}}
								},
								{//S block
									{{1,0},{2,0},{0,1},{1,1}},{{1,0},{1,1},{2,1},{2,2}},{{1,1},{2,1},{0,2},{1,2}},{{0,0},{0,1},{1,1},{1,2}}
								},
								{//Z block
									{{0,0},{1,0},{1,1},{2,1}},{{2,0},{1,1},{2,1},{1,2}},{{0,1},{1,1},{1,2},{2,2}},{{1,0},{0,1},{1,1},{0,2}}
								},
								{//J block
									{{0,0},{0,1},{1,1},{2,1}},{{1,0},{2,0},{1,1},{1,2}},{{0,1},{1,1},{2,1},{2,2}},{{1,0},{1,1},{0,2},{1,2}}
								},
								{//L block
									{{2,0},{0,1},{1,1},{2,1}},{{1,0},{1,1},{1,2},{2,2}},{{0,1},{1,1},{2,1},{0,2}},{{0,0},{1,0},{1,1},{1,2}}
								}
							 };
	const int rotRight = {
							{//state 0 to R
								{0,0},{-1,0},{-1,1},{0,-2},{-1,-2}
							},
							{//state 1/R to 2
								{0,0},{1,0},{1,-1},{0,2},{1,2}
							},
							{//state 2 to L
								{0,0},{1,0},{1,1},{0,-2},{1,-2}
							},
							{//state 3/L to 0
								{0,0},{-1,0},{-1,-1},{0,2},{-1,2}
							}
						};
	const int rotLeft = {
							{//state 0 to L
								{0,0},{1,0},{1,1},{0,-2},{1,-2}
							},
							{//state 1/R to 0
								{0,0},{1,0},{1,-1},{0,2},{1,2}
							},
							{//state 2 to R
								{0,0},{-1,0},{-1,1},{0,-2},{-1,-2}
							},
							{//state 3/L to 2
								{0,0},{-1,0},{-1,-1},{0,2},{-1,2}
							}
						};
	const int rotRightI = {
							{//state 0 to R
								{0,0},{-2,0},{1,0},{-2,-1},{1,2}
							},
							{//state 1/R to 2
								{0,0},{-1,0},{2,0},{-1,2},{2,-1}
							},
							{//state 2 to L
								{0,0},{2,0},{-1,0},{2,1},{-1,-2}
							},
							{//state 3/L to 0
								{0,0},{1,0},{-2,0},{1,-2},{-2,1}
							}
						};
	const int rotLeftI = {
							{//state 0 to L
								{0,0},{-1,0},{2,0},{-1,2},{2,-1}
							},
							{//state 1/R to 0
								{0,0},{2,0},{-1,0},{2,1},{-1,-2}
							},
							{//state 2 to R
								{0,0},{1,0},{-2,0},{1,-2},{-2,1}
							},
							{//state 3/L to 2
								{0,0},{-2,0},{1,0},{-2,-1},{1,2}
							}
						};
	int x, y;
	int typ, rot;
	bool hasSpawned = false;
	Tetris game;
public:
	void init(int posx, int posy, int ttype, Tetris &tgame);
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