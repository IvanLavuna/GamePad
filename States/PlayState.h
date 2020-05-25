//
// Created by ivan on 21.05.20.
//

#ifndef GAMEPAD_PLAYSTATE_H
#define GAMEPAD_PLAYSTATE_H

#include "State.h"
#include "Matrix.h"
#include <random>

class PlayState : public State
{
private:
	Matrix* matrix;
	std::map<int,BlockFigure*> blockFigures;

	BlockFigure* cur_figure;

	float timer;
	float speed;

	/// initialisation
	void initMatrix(sf::RenderWindow* window);
	void initBlockFigures();
	void initDefFigure();
public:
	explicit PlayState(sf::RenderWindow* window,std::stack<State*>* states);
	~PlayState() override;

	/// update
	void update(const float& dt) override;
	void updateInput(const float& dt) override;
	void updateTimer(const float& dt);

	/// render
	void render(sf::RenderTarget* target = nullptr) override;

	/// other
	void endState() override;
	void generateFigure();

};


#endif //GAMEPAD_PLAYSTATE_H
