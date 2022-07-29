#pragma once
#include <string>

using namespace std;

class Player
{
public:
	string name;
	int points;
	Player* leftPlayer;
	Player* rightPlayer;

	Player(string name);
};
