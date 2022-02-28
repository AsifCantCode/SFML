#include<iostream>
#include "Game.h"


//using namespace sf;

int main()
{
	//Init srand
	
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init Game engine
	Game game;

	//Game Loop
	while (game.running() && !game.getEndGame())
	{
		//Update
		game.update();

		//Render
		game.render();
	}

	//End of Application
	return 0;
}