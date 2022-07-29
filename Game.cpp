#include "Game.h"

// Preprocessor macro for readability.
#ifndef CLEAR_SCREEN
#define CLEAR_SCREEN system("CLS");
#endif // !CLEAR_SCREEN

// Wrappers for cin/cout replacement
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
// End of wrappers


void Game::SetUpPlayers()
{
	print("How many players would you like to have?");
	int playerCount = intinput();
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

		print(players[i].name + ": Left - " + players[i].leftPlayer->name + ", Right - " + players[i].rightPlayer->name + "\n");
	}

	print("Player setup complete, press enter to continue.");
	while (std::cin.get() != '\n');
	CLEAR_SCREEN
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
			message += " and passed a chip to " + currentPlayer.leftPlayer->name + ".\n";
			break;
		case 2:
			currentPlayer.points -= 1;
			message += " and put a chip in the center.\n";
			break;
		case 3:
			currentPlayer.rightPlayer->points += 1;
			currentPlayer.points -= 1;
			message += " and passed a chip to " + currentPlayer.rightPlayer->name + ".\n";
			break;
		default:
			message += ", keeping their chip.\n";
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
			}
			else
			{
				print("" + p.name + " doesn't have any points, so they passed to the player on their left.");
			}
		}

		print("\n-==- -==- -==- -==- -==- -==- -==- -==-\n");
		for (Player& p : this->players)
		{
			print(p.name + " has " + to_string(p.points) + " chips left.\n");
		}

		cout << "Round over, press enter to continue.";
		while (std::cin.get() != '\n');
		CLEAR_SCREEN

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
			string s;
			cout << "Game over!  Press enter to exit.";
			while (cin.get() != '\n');
		}
	}
}