#include "player.h"
void Player::setPlayerMark(const std::string &mark){
	player_mark = mark;
}
std::string Player::getPlayerMark(){
	return player_mark;
}
void Player::incrementMarkCount(){
	gameStat++;
}
void Player::resetMarkCount(){
	gameStat = 0;
}
int Player::getMarkCount(){
	return gameStat;
}
