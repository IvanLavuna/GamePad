//
// Created by ivan on 17.05.20.
//

#ifndef GAMEPAD_GAMESTATE_H
#define GAMEPAD_GAMESTATE_H
#include "gui.h"
#include "PlayState.h"

class GameState : public State
{
private:
	/// variables
	gui::GameBar* gameBar;

	/// initialisation
	void initGameBar();

public:
	explicit GameState(sf::RenderWindow* window,std::stack<State*>* states);
	~GameState() override;

	/// update
	void update(const float& dt) override;
	void updateInput(const float& dt) override;

	/// render
	void render(sf::RenderTarget* target = nullptr) override;

	/// other
	void endState() override;

};


#endif //GAMEPAD_GAMESTATE_H
