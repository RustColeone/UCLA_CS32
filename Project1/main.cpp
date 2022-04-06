// garks.cpp

#include <iostream>
#include <string>
#include <utility>

#include "Mesa.h"
#include "Game.h"
#include "globals.h"
#include "Player.h"
#include "Gark.h"
using namespace std;


///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}