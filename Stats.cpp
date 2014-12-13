//Stats.cpp

Stats::Stats()
{
	totalLines = 0;
	linesNextLvl = 0;
	score = 0;
	level = 1;
	comboCnt = 0;
	challenge = false;
	lineReqs = 20;
}
int Stats::calcScore(int lines)
{
	int tScore = 0;
	int b2bMult = 1.5;
	if(lines == 1)
	{
		tScore = 100 * level;
	}
	else if(lines == 2)
	{
		tScore = 300 * level;
	}
	else if(lines == 3)
	{
		tScore = 500 * level;
	}
	else
	{
		tScore = 800 * level;
		if(challenge == true)
		{
			tScore *= b2bMult;
		}
	}
	if(stats.comboCnt > 0)
	{
		tScore += 50 * comboCnt * level;
	}
	comboCnt++;
	return tScore;
}
void Stats::statUpdate(int lines)
{
	if(lines == 0)
	{
		comboCnt = 0;
	}
	else 
	{
		if(lines < 4)
		{
			challenge = false;
		}
		score += calcScore(lines);
		if(lines == 4)
		{
			challenge = true;
			//bonus line for tetris
			lines++;
		}
		lineUpdate(lines);
	}
}
void Stats::lineUpdate(int lines)
{
	totalLines += lines;
	linesNextLvl -= lines;
	while(linesNextLvl <=0)
	{
		level++;
		lineReqs = linesPerLevel * level;
		linesNextLvl += lineReqs;
	}
}
int Stats::getScore()
{
	return score;
}
void Stats::reset()
{
	totalLines = 0;
	linesNextLvl = 0;
	score = 0;
	level = 1;
	comboCnt = 0;
	challenge = false;
}
void Stats::start(int level)
{
	if(level > 0)
	{
		level = level;
	}
	else
	{
		level = 1;
	}
	lineReqs = linesPerLevel * level;
	linesNextLvl = lineReqs;
}

int getLevel()
{
	return level;
}