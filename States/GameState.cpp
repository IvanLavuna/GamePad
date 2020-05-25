//
// Created by ivan on 17.05.20.
//

#include "GameState.h"

/// constructors/destructors
GameState::GameState(sf::RenderWindow* window,std::stack<State*>* states)
	: State(window,states)
{
	this->initGameBar();
	this->window->setView(this->window->getDefaultView());

}

GameState::~GameState()
{
	delete gameBar;
}


/// initialisation
void GameState::initGameBar()
{
	gameBar = new gui::GameBar(this->window->getSize());
}

void GameState::endState()
{

}

/// update
void GameState::updateInput(const float &dt)
{
	if(!this->gameBar->isRenderingText())
	{
		this->gameBar->setRenderState();
		states->push(new PlayState(this->window, this->states));
	}

}

void GameState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->gameBar->update(this->mousePosView, this->states);
}

/// render
void GameState::render(sf::RenderTarget* target)
{
	this->gameBar->render(target);
}




