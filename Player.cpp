#include "Player.h"

Player::Player(string name)
{
	this->name = name;
	this->points = 0;
	this->leftPlayer = nullptr;
	this->rightPlayer = nullptr;
}