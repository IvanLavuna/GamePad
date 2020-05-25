//
// Created by ivan on 16.05.20.
//

#ifndef GAMEPAD_STATE_H
#define GAMEPAD_STATE_H
#include "Entity.h"


class State
{
private:

protected:
	/// variables
	sf::RenderWindow* window;
	std::stack<State*>* states;

	/// mouse positions
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
public:

	State(sf::RenderWindow* window,	std::stack<State*>* states);
	virtual ~State();

	/// functions
	/** to save or do something like that **/
	virtual void endState() = 0;

	/// update
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	/// render
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#endif //GAMEPAD_STATE_H
