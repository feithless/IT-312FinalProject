#include "dice.h"

using namespace std;

/// <summary>
/// Rolls a 6 sided die and returns the result.
/// </summary>
/// <returns>Result of the die roll.</returns>
int Dice::RollDie()
{
	return RollDie(6);
};

/// <summary>
/// Rolls an x sided die and returns the value.
/// </summary>
/// <param name="numberOfSides">Number of sides on the die.</param>
/// <returns>Result of the die roll.</returns>
int Dice::RollDie(int numberOfSides)
{
	return rand() % numberOfSides + 1;
};

/// <summary>
/// Rolls x number of six sided dice.
/// </summary>
/// <param name="numberOfDice">Number of dice to roll.</param>
/// <returns>Results of the roll in a vector format.</returns>
vector<int> Dice::RollDice(int numberOfDice)
{
	return RollDice(6, numberOfDice);
};

/// <summary>
/// Rolls x number of y sided dice.
/// </summary>
/// <param name="numberOfSides">Number of sides per die.</param>
/// <param name="numberOfDice">Number of dice to roll.</param>
/// <returns>Results of the roll in a vector format.</returns>
vector<int> Dice::RollDice(int numberOfSides, int numberOfDice)
{
	vector<int> dice;

	for (int i = 0; i < numberOfDice; i++)
		dice.push_back(rand() % numberOfSides + 1);

	return dice;
};
