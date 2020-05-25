//
// Created by ivan on 16.05.20.
//

#include "State.h"

/// constructors/destructors
State::State(sf::RenderWindow* window,	std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
}

State::~State()
{
}

/// functions

/// update
void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}