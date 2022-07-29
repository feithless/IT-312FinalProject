#pragma once

#include <ctime>
#include <iostream>
#include <vector>

class Dice
{
public:
	static int RollDie();
	static int RollDie(int numberOfSides);
	static std::vector<int> RollDice(int numberOfDice);
	static std::vector<int> RollDice(int numberOfSides, int numberOfDice);
};

