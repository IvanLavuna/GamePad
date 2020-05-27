//
// Created by ivan on 25.05.20.
//

#include "PlayersMenuState.h"

/// constructors/destructor
PlayersMenuState::PlayersMenuState(sf::RenderWindow *window, std::stack<State *> *states)
	: State(window, states)
{
	this->initFont();
	this->initButtons();
	this->initBackground(window->getSize());
}

PlayersMenuState::~PlayersMenuState()
{
	delete this->onePlayer;
	delete this->twoPlayers;
	delete this->goMenu;
	delete this->font;
}


/// initialisation
void PlayersMenuState::initButtons()
{
	this->onePlayer = new gui::Button(200, 100, 400, 80, "One player",this->font,
		sf::Color(124,190,228),sf::Color(92,142,171),
		sf::Color(41,67,81));

	this->twoPlayers = new gui::Button(200, 200, 400, 80, "Two players",this->font,
									  sf::Color(124,190,228),sf::Color(92,142,171),
									  sf::Color(41,67,81));

	this->goMenu = new gui::Button(200, 300, 400, 80, "Go menu",this->font,
									   sf::Color(124,190,228),sf::Color(92,142,171),
									   sf::Color(41,67,81));
}

void PlayersMenuState::initFont()
{
	this->font = new sf::Font();
	if(!this->font->loadFromFile("../Fonts/Amatic-Bold.ttf"))
	{
		std::cerr << "File ../Fonts/Amatic-Bold.ttf couldn't be opened" << std::endl;
	}
}

void PlayersMenuState::initBackground(sf::Vector2u rect)
{
	this->background = sf::RectangleShape(sf::Vector2f(rect));
	this->background.setFillColor(sf::Color(126,240,225));
}

/// update
void PlayersMenuState::update(const float &dt)
{
	this->updateInput(dt);
	this->twoPlayers->update(this->mousePosView);
	this->onePlayer->update(this->mousePosView);
	this->goMenu->update(this->mousePosView);
}

void PlayersMenuState::updateInput(const float &dt)
{
	if(this->onePlayer->isPressed(this->mousePosView))
	{
		this->states->push(new GameState(this->window, this->states,1));
	}
	if(this->twoPlayers->isPressed(this->mousePosView))
	{
		this->states->push(new GameState(this->window, this->states,2));
	}
	if(this->goMenu->isPressed(this->mousePosView))
	{
		this->states->pop();
	}
}

/// render
void PlayersMenuState::render(sf::RenderTarget *target)
{
	target->draw(this->background);
	this->onePlayer->render(target);
	this->twoPlayers->render(target);
	this->goMenu->render(target);
}

void PlayersMenuState::endState()
{

}
