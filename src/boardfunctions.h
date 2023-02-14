#include <iostream>
#include <string>
#include <regex>
#include <tuple>
#include <cmath>
#include <iterator>
#include "player.h"
#include <array>
class BoardGame {
public:
	int startGame();
	void printTable();
	void promptPlayer(Player &player);
	bool calculateSlope(int x, int y, int &board_x, int &board_y);
	int findOrigin(int &rowsize);
	std::tuple<int,int,int> getXY(int X, int Y, int &origin);
	std::array<int,2> rotMatrixMultiply(const int &degrees, int pos[]);
	bool calculateVictory(Player &player);
	void markPosition(int &r, int &c, const std::string &mark);
private:
	std::string game[3][3];
};
