//
// Created by ivan on 18.05.20.
//

#ifndef GAMEPAD_MAINMENUSTATE_H
#define GAMEPAD_MAINMENUSTATE_H
#include "State.h"
#include "gui.h"
#include "BurstAnimation.h"
#include "GameState.h"

class MainMenuState : public State
{
private:
	/// variables
	sf::RectangleShape background;
	sf::Text gameText; /// text of the game
	sf::Font* font;

	std::map<std::string,gui::Button*> buttons;

	BurstAnimation* burstAnim;

	/// Initialisation
	void initFonts();
	void initButtons();
	void initGameText();
	void initBackground(sf::RenderWindow* window = nullptr);
	void initAnimations();

public:
	/// constructors/destructor
	explicit MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);

	~MainMenuState() override;

	/// functions
	void endState() override;

	/// update
	void updateButtons();
	void updateInput(const float& dt) override; /// not events
	void update(const float& dt) override ;
	void updateAnimations();

	/// render
	void render(sf::RenderTarget* target = nullptr) override;
	void renderButtons(sf::RenderTarget* target);



};


#endif //GAMEPAD_MAINMENUSTATE_H
