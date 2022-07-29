#pragma once

#include "dice.h"
#include "Player.h"


using namespace std;

class Game
{
	vector<Player> players;

	void SetUpPlayers();

	int RollDice(Player& currentPlayer);

	int PlayersIn();

	void GameOver();

public:
	Game();

	void PlayGame();
};

