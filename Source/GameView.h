//
// Created by ivan on 25.05.20.
//

#ifndef GAMEPAD_GAMEVIEW_H
#define GAMEPAD_GAMEVIEW_H

#include "Matrix.h"

/** logic and game are defined all here **/
class GameView
{
private:
	/// variables
	sf::View view;
	sf::RenderWindow* window;

	Matrix* matrix;
	Tetromino* curTetromino;

	sf::Font* font;
	sf::Text scoreString;
	int score;

	bool lostState;
	float timer;

	sf::RectangleShape background;
	std::map<int,TetrominoType> tetroMap;
	/** color palette **/
	std::vector<sf::Color> colors;

	/// initialisation
	void initGame();
	void initScore();
	void initBackground();
	void initTetroMap();
	void initColorPalette();
public:
	GameView(sf::FloatRect viewRect,sf::RenderWindow* window);
	~GameView();

	/// update
	void update(const float& dt);
	void updateInput();
	void updateTetromino(const float& dt);
	void updateScore();
	void updateTimer(const float& dt);

	/// render
	void render();
	void renderLostState();

	/// core
	void generateNewTetromino();
	void checkLostState();
};


#endif //GAMEPAD_GAMEVIEW_H
