#include <string>
#pragma once
class Player {
public:
	void setPlayerMark(const std::string &mark);
	std::string getPlayerMark();
	void resetMarkCount();
	void incrementMarkCount();
	int getMarkCount();
private:
	std::string player_mark;
	int gameStat;
};
