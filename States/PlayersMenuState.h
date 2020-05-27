//
// Created by ivan on 25.05.20.
//

#ifndef GAMEPAD_PLAYERSMENUSTATE_H
#define GAMEPAD_PLAYERSMENUSTATE_H

#include "GameState.h"

class PlayersMenuState : public State
{
private:
	/// variables
	/** buttons **/
	gui::Button* onePlayer;
	gui::Button* twoPlayers;
	gui::Button* goMenu;

	sf::RectangleShape background;
	sf::Font* font;

	/// initialisation
	void initButtons();
	void initFont();
	void initBackground(sf::Vector2u rect);
public:
	explicit PlayersMenuState(sf::RenderWindow* window,std::stack<State*>* states);
	~PlayersMenuState() override;

	/// update
	void update(const float& dt) override;
	void updateInput(const float& dt) override;

	/// render
	void render(sf::RenderTarget* target = nullptr) override;

	/// other
	void endState() override;
};


#endif //GAMEPAD_PLAYERSMENUSTATE_H
