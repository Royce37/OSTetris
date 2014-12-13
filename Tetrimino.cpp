#include "Tetris.h"

void Tetrimino::init(int posx, int posy, int ttype, Tetris &tgame)
{
	x = posx;
	y = posy;
	typ = ttype;
	game = tgame;
	rot = 0;
	hasSpawned = true;
}

bool Tetrimino::canDrop()
{
	int deepRow = -1, col, j;
	//For each column, find the deepest row of the tetrimino, and check the next row for collision
	for(col = 0; col < PIECE_SIZE; col++)
	{
		//Check each coord to see if it has the same column
		for(j = 0; j < pieces[type][rot].length; j++)
		{
			if(pieces[type][rot][j][0] === col && pieces[type][rot][j][1] > deepRow)
			{
				deepRow = pieces[type][rot][j][1];
			}
		}
		if(deepRow >= 0)
		{
			if(y+deepRow+1 >= ROWS || game.matrix[y+deepRow+1][x+col] != 0)
			{
				return false;
			}
		}
		deepRow = -1;
	}
	return true;
}

void Tetrimino::drop()
{
	int i;
	int offX, offY;
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = 0;
	}
	y++;
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = typ;
	}
}

bool Tetrimino::checkLeft()
{
	int leftCol = 4, row, j;
	//For each row, find the left most column of the tetrimino, and check the next left column for collision
	for(row = 0; row < 4; row++)
	{
		//Check each coord to see if it has the same row
		for(j = 0; j < PIECE_SIZE; j++)
		{
			if(pieces[type][rot][j][1] === row && pieces[type][rot][j][0] < leftCol)
			{
				leftCol = pieces[type][rot][j][0];
				//log(leftCol);
			}
		}
		if(leftCol <= 3)
		{
			if(x+leftCol-1 < 0 || game.matrix[y+row][x+leftCol-1] != 0)
			{
				return false;
			}
		}
		leftCol = 4;
	}
	return true;
}

void Tetrimino::moveLeft()
{
	int i, offX, offY;
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = 0;
	}
	x--;
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = typ;
	}
}

bool Tetrimino::checkRight()
{
	int rightCol = -1, row, j;
	//For each row, find the right most column of the tetrimino, and check the next right column for collision
	for(row = 0; row < 4; row++)
	{
		//Check each coord to see if it has the same row
		for(j = 0; j < PIECE_SIZE; j++)
		{
			if(pieces[type][rot][j][1] === row && pieces[type][rot][j][0] > rightCol)
			{
				rightCol = pieces[type][rot][j][0];
				//log(rightCol);
			}
		}
		if(rightCol >= 0)
		{
			if(x+rightCol+1 >= COL || game.matrix[y+row][x+rightCol+1] != 0)
			{
				return false;
			}
		}
		rightCol = -1;
	}
	return true;
}

void Tetrimino::moveRight()
{
	int i, offX, offY;
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = 0;
	}
	x++;
	for(var i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = typ;
	}
}

bool Tetrimino::checkRotateRight()
{
	int testRot = (rot+1)%4;
	int tempX = x;
	int tempY = y;
	int *offset = NULL; 
	int testcase, baseX, baseY, i;
	bool pass;
	for(testCase = 0; testCase < ROT_SIZE; testCase++)
	{
		pass = true;
		if(typ == 1)
		{
			for(i = 0; i < PIECE_SIZE && pass == true; i++)
			{
				//Test where the tetrimino would rotate to
				baseX = tempX + pieces[type][testRot][i][0] + rotRightI[rot][testCase][0];
				baseY = tempY + pieces[type][testRot][i][1] + rotRightI[rot][testCase][1];
				if(baseX < 0 || baseX >= COL || baseY < 0 || baseY >= ROWS)
				{
					pass = false;
				}
				else if(game.matrix[baseY][baseX] != 0)
				{
					pass = false;
				}
			}
			if(pass == true)
			{
				offset = rotRightI[rot][testCase];
				return offset;
			}
		}
		else
		{
			for(var i = 0; i < PIECE_SIZE && pass == true; i++)
			{
				//Test where the tetrimino would rotate to
				baseX = tempX + pieces[type][testRot][i][0] + rotRight[rot][testCase][0];
				baseY = tempY + pieces[type][testRot][i][1] + rotRight[rot][testCase][1];
				if(baseX < 0 || baseX >= COL || baseY < 0 || baseY >= ROWS)
				{
					pass = false;
				}
				else if(game.matrix[baseY][baseX] != 0)
				{
					pass = false;
				}
			}
			if(pass == true)
			{
				offset = rotRight[rot][testCase];
				return offset;
			}
		}
	}
	return NULL;
}

void Tetrimino::rotateRight()
{
	int i, offX, offY;
	int *offset = NULL;
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = 0;
	}
	offset = checkRotateRight();
	//log(offset);
	if(offset != NULL)
	{
		rot = (rot+1)%4;
		x += offset[0];
		y += offset[1];
	}
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = typ;
	}
}

bool Tetrimino::checkRotateLeft()
{
	int testRot = (tet.rot-1)%4;
	int tempX = tet.x;
	int tempY = tet.y;
	int *offset = NULL;
	bool pass;
	int testCase, i, baseX, baseY;
	for(testCase = 0; testCase < ROT_SIZE; testCase++)
	{
		pass = true;
		if(typ == 1)
		{
			//log("checkRotateLeft - I");
			for(i = 0; i < PIECE_SIZE && pass == true; i++)
			{
				//Test where the tetrimino would rotate to
				baseX = tempX + pieces[type][testRot][i][0] + rotLeftI[rot][testCase][0];
				baseY = tempY + pieces[type][testRot][i][1] + rotLeftI[rot][testCase][1];
				if(baseX < 0 || baseX >= COL || baseY < 0 || baseY >= ROWS)
				{
					pass = false;
				}
				else if(game.matrix[baseY][baseX] != 0)
				{
					pass = false;
				}
			}
			if(pass == true)
			{
				offset = rotLeftI[rot][testCase];
				return offset;
			}
		}
		else
		{
			for(i = 0; i < PIECE_SIZE && pass == true; i++)
			{
				//Test where the tetrimino would rotate to
				baseX = tempX + pieces[type][testRot][i][0] + rotLeft[rot][testCase][0];
				baseY = tempY + pieces[type][testRot][i][1] + rotLeft[rot][testCase][1];
				//log("X value: " + baseX + " Y value: " + baseY);
				if(baseX < 0 || baseX >= COL || baseY < 0 || baseY >= ROWS)
				{
					pass = false;
				}
				else if(game.matrix[baseY][baseX] != 0)
				{
					pass = false;
				}
			}
			if(pass == true)
			{
				offset = rotLeft[rot][testCase];
				return offset;
			}
		}
	}
	return NULL;
}

void Tetrimino::rotateLeft()
{
	int i, offX, offY;
	int *offset = NULL;
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = 0;
	}
	offset = checkRotateLeft();
	//log(offset);
	if(offset != null)
	{
		rot = (rot-1)%4;
		x += offset[0];
		y += offset[1];
	}
	for(i = 0; i < PIECE_SIZE; i++)
	{
		offX = pieces[type][rot][i][0];
		offY = pieces[type][rot][i][1];
		game.matrix[y+offY][x+offX] = typ;
	}
}

void Tetrimino::setActive(bool set)
{
	hasSpawned = set;
}
bool isActive()
{
	return hasSpawned;
}