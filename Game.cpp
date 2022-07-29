#include "Game.h"

// Wrappers for cin/cout replacement and clearing the console.
void print(string msg)
{
	cout << msg << endl;
}

string input(std::string msg)
{
	string innerput;
	print(msg);
	cin >> innerput;
	return innerput;
}

string input()
{
	return input("");
}

int intinput(std::string msg)
{
	int input;
	do {
		print(msg);
		cin >> input;
		
		// Error checking for cin to ensure that it doesn't end up broken and stuck in a permanent loop.
		if (!cin)
		{
			print("Please only use whole numbers.");
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else 
			break;
	} while (true);
	return input;
}

int intinput()
{
	return intinput("");
}

void ClearScreen(string msg)
{
	print(msg + ", press enter to continue.");
	while (cin.get() != '\n');
	system("CLS");
}
// End of wrappers


void Game::SetUpPlayers()
{
	print("How many players would you like to have?");
	int playerCount = 0;

	while (playerCount < 3)
	{
		playerCount = intinput();
		if (playerCount < 3)
			print("There must be 3 or more players.");
	}


	for (int i = 1; i <= playerCount; i++)
	{
		string msg = "Please enter player " + to_string(i) + "'s name:";

		print(msg);
		string playerName = input();
		Player player = playerName;
		this->players.push_back(player);
	}

	print("Players have been set up!\n\n-=- -=- -=- -=- -=- -=- -=- -=- -=- -=- -=-");
	print("Printing current players:\n");

	for (int i = 0; i < playerCount; i++)
	{
		players[i].points = 3;

		// "(vectorCount + (i +/- 1)) % vectorCount" returns 0 -> (vectorCount - 1)
		players[i].rightPlayer = &players[(playerCount + (i + 1)) % playerCount];
		players[i].leftPlayer = &players[(playerCount + (i - 1)) % playerCount];

		// Mostly debug purposes.
		print(players[i].name + " is to the right of " + players[i].leftPlayer->name);
	}

	ClearScreen("Player setup complete");
}

int Game::RollDice(Player &currentPlayer)
{
	int numberOfDice = currentPlayer.points;
	
	if (numberOfDice > 3)
		numberOfDice = 3;

	int roll = 0;

	for (int i = 1; i <= numberOfDice; i++)
	{
		roll = Dice::RollDie();
		string message = "" + currentPlayer.name + " rolled a " + to_string(roll);
		
		// Roll of 1 pass to left, roll of 2 pass to center, roll of 3 pass to right
		// 4-6 don't matter.
		switch (roll)
		{
		case 1:
			currentPlayer.leftPlayer->points += 1;
			currentPlayer.points -= 1;
			message += " and passed a chip to " + currentPlayer.leftPlayer->name + ".";
			break;
		case 2:
			currentPlayer.points -= 1;
			message += " and put a chip in the center.";
			break;
		case 3:
			currentPlayer.rightPlayer->points += 1;
			currentPlayer.points -= 1;
			message += " and passed a chip to " + currentPlayer.rightPlayer->name + ".";
			break;
		default:
			message += ", keeping their chip.";
			break;
		}

		print(message);
	}

	return PlayersIn();
}



Game::Game()
{
	SetUpPlayers();
}

int Game::PlayersIn()
{
	int playersIn = 0;

	for (Player& p : players)
	{
		if (p.points > 0)
			playersIn++;
	}

	return playersIn;
}


void Game::PlayGame()
{
	do
	{
		for (Player &p : this->players)
		{
			if (p.points > 0)
			{
				int playersIn = RollDice(p);

				// If only one player left, break out of this for loop.
				if (playersIn == 1)
					goto END;
				print("");
			}
			else
			{
				print("" + p.name + " doesn't have any points, so they passed to the player on their left.\n");
			}
		}

		print("-==- -==- -==- -==- -==- -==- -==- -==-\n");
		for (Player& p : this->players)
		{
			print(p.name + " has " + to_string(p.points) + " chips left.");
		}

		ClearScreen("\nRound over");

	} while (true);

END:
	GameOver();
}


void Game::GameOver()
{
	for (Player& p : this->players)
	{
		if (p.points > 0)
		{
			print(p.name + " wins with " + to_string(p.points) + " chips left!");
			cout << "Game over!  Press enter to exit.";
			while (cin.get() != '\n');
		}
	}
}