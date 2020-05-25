//
// Created by ivan on 16.05.20.
//

#ifndef GAMEPAD_GAME_H
#define GAMEPAD_GAME_H

#include "GameState.h"
#include "MainMenuState.h"

class Game
{
private:
	/// Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;
	std::stack<State*> states;


	/// Initialisation
	void initWindow();
	void initStates();
public:
	/// Constructors/Destructor
	Game();
	virtual ~Game();

	/// Functions

	/// Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	/// render
	void render();

	/// core
	void run();
};


#endif //GAMEPAD_GAME_H





