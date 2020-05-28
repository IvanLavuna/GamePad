//
// Created by ivan on 25.05.20.
//

#ifndef GAMEPAD_GAMEVIEW_H
#define GAMEPAD_GAMEVIEW_H

#include "Matrix.h"
#include "gui.h"
#include <fstream>

/** logic and game are defined all here **/
class GameView
{
private:
	/// variables
	/// core
	sf::View view;
	sf::RenderWindow* window;
	std::stack<State*>* states;

	Matrix* matrix;
	Tetromino* curTetromino;

	sf::Font* font;
	sf::Text scoreString;
	int score;

	bool lostState;
	float timer;

	sf::RectangleShape background;
	std::map<int,TetrominoType> tetroMap;
	std::vector<sf::Color> colors;	/** color palette **/
	std::map<std::string,int> supportedKeys;
	std::map<std::string,int> gameKeys;
	gui::Button* goMenuBtn;

	/// initialisation
	void initGame();
	void initScore();
	void initBackground();
	void initTetroMap();
	void initColorPalette();
	void initKeyboardInput(std::string playerInputKeyboard);
	void initSupportedKeys();
	void initButtons();
public:
	GameView(sf::FloatRect viewRect, sf::RenderWindow* window,
			std::string playerInputKeyboard,std::stack<State*>* states);
	~GameView();

	/// update
	void update(const float& dt);
	void updateInput();
	void updateTetromino(const float& dt);
	void updateScore();
	void updateTimer(const float& dt);
	void updateGoMenuBtnInput();

	/// render
	void render();
	void renderLostState();

	/// core
	void generateNewTetromino();
	void checkLostState();
	void endState();
};


#endif //GAMEPAD_GAMEVIEW_H
