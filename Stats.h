//Stats.h

#ifndef _stat_h_defined_
#define _stat_h_defined_

class Stats
{
	int totalLines = 0;
	int linesNextLvl = 0;
	int score = 0;
	int level = 1;
	int comboCnt = 0;
	bool challenge = false;
	int lineReqs = 20;
	const int linesPerLevel = 4;

public:
	Stats();
	~Stats(){};
	int calcScore(int lines);
	void statUpdate(int lines);
	void lineUpdate(int lines);
	int getScore();
	void reset();
	void start(int level);
	int getLevel();
}
#endif