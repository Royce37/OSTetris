//Stats.h

#ifndef _stat_h_defined_
#define _stat_h_defined_

class Stats
{
	int totalLines;
	int linesNextLvl;
	int score;
	int level;
	int comboCnt;
	bool challenge;
	int lineReqs;
	static const int linesPerLevel = 4;

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
	void init();
};
#endif
