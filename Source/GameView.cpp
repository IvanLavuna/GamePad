//
// Created by ivan on 25.05.20.
//

#include "GameView.h"

/// constructors/destructor
GameView::GameView(sf::FloatRect viewRect,sf::RenderWindow* window,
				   std::string playerInputKeyboard,std::stack<State*>* states):
	lostState(false), window(window), timer(0), states(states)
{
	this->view.setViewport(viewRect);
	this->initColorPalette();
	this->initTetroMap();
	this->initGame();
	this->initBackground();
	this->initScore();
	this->initSupportedKeys();
	this->initKeyboardInput(playerInputKeyboard);
	this->initButtons();
}

GameView::~GameView()
{
	delete this->matrix;
	delete this->curTetromino;
	delete this->font;
	delete this->goMenuBtn;
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

void GameView::initSupportedKeys()
{
	std::ifstream file("../Config/supportedKeys.init");
	if(file.is_open())
	{
		int i = 0;
		std::string key ;
		while(file >> key)
		{
			this->supportedKeys[key] = i;
			i++;
		}
		file.close();
	}
	else
	{
		std::cerr << "File ../Config/supportedKeys.init couldn't be opened.\n";
	}
}

void GameView::initKeyboardInput(std::string playerInputKeyboard)
{
	std::ifstream file(playerInputKeyboard);
	if(file.is_open())
	{
		std::string key;
		std::string keyValue;
		while(file >> key >> keyValue)
		{
			this->gameKeys[key] = supportedKeys[keyValue];
		}
		file.close();
	}
	else
	{
		std::cerr << "File ../Config/player1.init couldn't be opened." << std::endl;
	}

}

void GameView::initButtons()
{
	this->goMenuBtn = new gui::Button(0,0,200,75,
			"go menu",this->font,sf::Color(124,190,228),sf::Color(92,142,171),
								   sf::Color(41,67,81));
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
	else
	{
		this->goMenuBtn->update(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
		this->updateGoMenuBtnInput();
	}
}

void GameView::updateInput()
{
	/// move left
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->gameKeys["MOVE_LEFT"]))
	   && this->timer > 0.15f
	   && this->curTetromino->canMoveLeft(this->matrix))
	{
		curTetromino->moveLeft();
		timer = 0;
	}
	/// move right
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->gameKeys["MOVE_RIGHT"]))
	   && this->timer > 0.15f
	   && this->curTetromino->canMoveRight(this->matrix))
	{
		curTetromino->moveRight();
		timer = 0;
	}
	/// move down
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->gameKeys["MOVE_DOWN"]))
		&& this->timer > 0.15f)
	{
		curTetromino->moveDown();
		timer = 0;
	}
	/// rotate
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->gameKeys["ROTATE"]))
		&& this->timer > 0.15f)
	{
		curTetromino->RotateLeft();
		timer = 0;
	}
	/// teleportate on projection
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->gameKeys["TELEPORTATE"]))
		&& this->timer > 0.20f)
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

void GameView::updateGoMenuBtnInput()
{
	if(this->goMenuBtn->isPressed(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window))))
	{
		this->endState();
		this->states->pop();
	}
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
	this->window->draw(this->scoreString);
	this->scoreString.setCharacterSize(300);
	this->scoreString.setPosition(this->view.getSize().x/5.0,this->view.getSize().y/ 3.5);
	this->goMenuBtn->render(this->window);
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

void GameView::endState()
{
	this->window->setView(window->getDefaultView());
}









