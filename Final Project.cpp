#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "Game.h"

using namespace std;


int main()
{
    // Proper randomizing.
    srand((unsigned)time(NULL));

    Game LCR;

    LCR.PlayGame();

}
