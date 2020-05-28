//
// Created by ivan on 17.05.20.
//

#include "GameState.h"

/// constructors/destructors
GameState::GameState(sf::RenderWindow* window,std::stack<State*>* states, uint players)
	: State(window,states)
{
	std::string fileNameStart("../Config/player"), fileNameEnd(".init");
	for(int i = 0;i < players;i++)
	{
		this->games[i] = new GameView(sf::FloatRect(1.f/float(players) * float(i),0,1.f/float(players),1.f),
				window, fileNameStart + std::to_string(i + 1) + fileNameEnd,this->states);
	}
}

GameState::~GameState()
{
	this->games.clear();
}


/// initialisation

void GameState::endState()
{

}

/// update
void GameState::updateInput(const float &dt)
{

}

void GameState::update(const float& dt)
{
	for(auto& item: this->games)
		item.second->update(dt);
}

/// render
void GameState::render(sf::RenderTarget* target)
{
	for(auto& item: this->games)
		item.second->render();
}




