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
	bool victoryOnSlope(Player &player, const int &origin);
	bool victoryOnStraightLine(Player &player, const int &origin);
	bool calculateSlope(int x, int y, int &board_x, int &board_y);
	int findOrigin(const int &rowsize);
	std::tuple<int,int> getXY(int X, int Y, const int &origin);
	std::array<int,2> rotMatrixMultiply(const double &degrees, int pos[]);
	bool calculateVictory(Player &player);
	void markPosition(int &r, int &c, const std::string &mark);
private:
	std::string game[3][3];
	const int y_max = sizeof(this->game) / sizeof(this->game[0]);
	const int x_max = sizeof(this->game[0])/ sizeof(std::string);
};
