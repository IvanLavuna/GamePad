//
// Created by ivan on 25.05.20.
//

#include "GameView.h"

/// constructors/destructor
GameView::GameView(sf::FloatRect viewRect,sf::RenderWindow* window):
	lostState(false), window(window),timer(0)
{
	this->view.setViewport(viewRect);
	this->initColorPalette();
	this->initTetroMap();
	this->initGame();
	this->initBackground();
	this->initScore();
}

GameView::~GameView()
{
	delete this->matrix;
	delete this->curTetromino;
	delete this->font;
}

/// initialisation
void GameView::initGame()
{
	this->matrix = new Matrix(sf::Vector2u (view.getSize()));
	this->generateNewTetromino();
}


void GameView::initScore()
{
	this->font = new sf::Font();
	if(!this->font->loadFromFile("../Fonts/Amatic-Bold.ttf"))
	{
		std::cerr << "file ../Fonts/Amatic-Bold.ttf could not be opened" << std::endl;
	}

	score = 0;
	scoreString.setString("score: " + std::to_string(score));
	scoreString.setFont(*this->font);
	scoreString.setCharacterSize(75);
	scoreString.setPosition(this->view.getSize().x - 180,10 );
	scoreString.setFillColor(sf::Color(126,149,34));
}

void GameView::initBackground()
{
	this->background = sf::RectangleShape(this->view.getSize());
	this->background.setFillColor(this->matrix->getColor());
}

void GameView::initTetroMap()
{
	this->tetroMap[1] = FIRSTTETROMINO;
	this->tetroMap[2] = SECONTETROMINO;
	this->tetroMap[3] = THIRDTETROMINO;
	this->tetroMap[4] = FOURTHTETROMINO;
	this->tetroMap[5] = FIFTHTETROMINO;
	this->tetroMap[6] = SIXTHTETROMINO;
	this->tetroMap[7] = SEVENTHTETROMINO;
}

void GameView::initColorPalette()
{
	this->colors.reserve(10);
	this->colors.emplace_back(51,102,0);
	this->colors.emplace_back(153,153,0);
	this->colors.emplace_back(0,176,153);
	this->colors.emplace_back(0,0,204);
	this->colors.emplace_back(255,0,255);
	this->colors.emplace_back(0,0,102);
	this->colors.emplace_back(51,225,153);
	this->colors.emplace_back(153,51,255);
	this->colors.emplace_back(51,255,51);
	this->colors.emplace_back(153,0,76);
}

/// update
void GameView::update(const float &dt)
{
	this->updateTimer(dt);
	this->checkLostState();
	if(!this->lostState)
	{
		this->updateInput();
		this->updateTetromino(dt);
		this->updateScore();
	}
}

void GameView::updateInput()
{
	/// move left
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->timer > 0.15f
	   && this->curTetromino->canMoveLeft(this->matrix))
	{
		curTetromino->moveLeft();
		timer = 0;
	}
	/// move right
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->timer > 0.15f
	   && this->curTetromino->canMoveRight(this->matrix))
	{
		curTetromino->moveRight();
		timer = 0;
	}
	/// move down
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->timer > 0.15f)
	{
		curTetromino->moveDown();
		timer = 0;
	}
	/// rotate
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->timer > 0.15f)
	{
		curTetromino->RotateLeft();
		timer = 0;
	}
	/// teleportate on projection
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& this->timer > 0.20f)
	{
		curTetromino->LandDown(this->matrix);
		timer = 0;
	}
}

void GameView::updateTetromino(const float &dt)
{
	this->curTetromino->updateTimer(dt);
	if(this->curTetromino->canFall(this->matrix))
		this->curTetromino->fall(dt);
	else
	{
		this->matrix->checkLines();
		this->matrix->engrave(this->curTetromino);
		this->matrix->checkLines();
		delete this->curTetromino;
		this->generateNewTetromino();
		this->score += 4;
	}
}

void GameView::updateScore()
{
	this->scoreString.setString("score: " + std::to_string(score));
}

void GameView::updateTimer(const float& dt)
{
	this->timer += dt;
}

/// render
void GameView::render()
{
	if(!this->lostState)
	{
		this->window->setView(this->view);
		this->matrix->renderMatrix(window);
		this->matrix->renderLines(window);
		this->matrix->renderTetromino(window, this->curTetromino);
		this->matrix->renderProjection(this->window, this->curTetromino);
		this->window->draw(this->scoreString);
	} else
		this->renderLostState();
}

void GameView::renderLostState()
{
	this->window->setView(this->view);
	this->matrix->renderMatrix(window);
	this->matrix->renderLines(window);
	this->matrix->renderTetromino(window, this->curTetromino);
//	this->matrix->renderProjection(this->window, this->curTetromino);
	this->window->draw(this->scoreString);

}

/// core
void GameView::generateNewTetromino()
{
	int randValue = rand() % 7 + 1;
	int randColor = rand() % 9;
	this->curTetromino = new Tetromino(this->tetroMap[randValue]);
	this->curTetromino->setColor(this->colors[randColor]);
	this->curTetromino->setPosition(5,1);
}

void GameView::checkLostState()
{
	this->lostState = this->matrix->checkFirstLine();
}






