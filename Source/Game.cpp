//
// Created by ivan on 16.05.20.
//

#include "Game.h"

/// Static functions

/// Constructors/Destructor
Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while(!this->states.empty())
		this->states.pop();

}


/// Initializer functions
void Game::initWindow()
{
	std::ifstream file("../Config/Window.init");

	std::string title = "None";
	sf::VideoMode window_bounds(800,600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if(file.is_open())
	{
		std::getline(file,title);
		file >> window_bounds.width >> window_bounds.height;
		file >> framerate_limit;
		file >> vertical_sync_enabled;
	}
	file.close();
	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);

}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window,&this->states));
}


/// regular functions
void Game::updateDt()
{
	/** Updates dt variable with the time it takes to update and render one frame **/
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while(window->pollEvent(sfEvent))
	{
		switch (sfEvent.type)
		{
			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::Resized:

			default:
				break;
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if(!this->states.empty())
		this->states.top()->update(dt);
}

void Game::render()
{
	this->window->clear();

	if(!this->states.empty())
		this->states.top()->render(this->window);


	this->window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}







