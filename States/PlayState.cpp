//
// Created by ivan on 21.05.20.
//

#include "PlayState.h"

PlayState::PlayState(sf::RenderWindow *window, std::stack<State *> *states):
	State(window, states), timer(0), speed(80)
{
	this->initMatrix(this->window);
	this->initBlockFigures();
	this->initDefFigure();
	this->generateFigure();
}

PlayState::~PlayState()
{
	delete this->matrix;
	this->blockFigures.clear();
	delete this->cur_figure;

}

/// initialisation
void PlayState::initMatrix(sf::RenderWindow *window)
{
	this->matrix = new Matrix(16,12,
			sf::FloatRect(0.0f,0.0f,0.5f,1.f),this->window);
}

void PlayState::initBlockFigures()
{
	/// 1
	sf::Color color1 = sf::Color(31,218,69);
	std::vector<std::pair<int,int>> figure1 = { {2,0},{0,0}, {1,0}, {3,0}};
	blockFigures[1] = new BlockFigure(figure1,color1);

	///2
	sf::Color color2 = sf::Color(49,152,70);
	std::vector<std::pair<int,int>> figure2 = {{1,1}, {0,0}, {0,1}, {2,1}};
	blockFigures[2] = new BlockFigure(figure2, color2);

	///3
	sf::Color color3 = sf::Color(49,152,70);
	std::vector<std::pair<int,int>> figure3 = {  {1,1},{0,1},{2,1}, {2,0}};
	blockFigures[3] = new BlockFigure(figure3, color3);

	///4
	sf::Color color4 = sf::Color(49,152,70);
	std::vector<std::pair<int,int>> figure4 = { {0,0}, {0,1},{1,0}, {1,1}};
	blockFigures[4] = new BlockFigure(figure4, color4);

	///5
	sf::Color color5 = sf::Color(49,152,70);
	std::vector<std::pair<int,int>> figure5 = { {1,1},{0,1},{1,0}, {2,0}};
	blockFigures[5] = new BlockFigure(figure5, color5);

	///6
	sf::Color color6 = sf::Color(49,152,70);
	std::vector<std::pair<int,int>> figure6 = {  {1,1},{0,1},{2,1}, {1,0}};
	blockFigures[6] = new BlockFigure(figure6, color6);

	///7
	sf::Color color7 = sf::Color(49,152,70);
	std::vector<std::pair<int,int>> figure7 = { {1,1},{0,0}, {1,0}, {2,1}};
	blockFigures[7] = new BlockFigure(figure7, color7);
}

void PlayState::initDefFigure()
{
	this->cur_figure = new BlockFigure(*blockFigures[1]);
}

/// update
void PlayState::update(const float &dt)
{
	this->updateInput(dt);
	this->updateTimer(dt);
	this->cur_figure->updateTimer(this->speed,dt);
	this->cur_figure->fall(dt);
	this->cur_figure->checkCoordinatesForFalling(matrix->getHeight());
	if(!cur_figure->Fallen() || !this->matrix->canFall(this->cur_figure))
	{
		this->matrix->stopFigure(this->cur_figure);
		this->generateFigure();
	}
	this->matrix->checkForRows();
	if(this->matrix->hasFirstRow())
	{
		this->states->pop();
		this->states->top()->update(dt);
	}
}

void PlayState::updateInput(const float &dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->timer > 10
	&& this->cur_figure->getLeftMostCoordinate() > 0)
	{
		cur_figure->moveLeft(dt);
		timer = 0;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->timer > 10 &&
		this->cur_figure->getRightMostCoordinate() < this->matrix->getHeight() - 5)
	{
		cur_figure->moveRight(dt);
		timer = 0;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->timer > 10)
	{
		cur_figure->moveDown(dt);
		timer = 0;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->timer > 10)
	{
		cur_figure->RotateLeft();
		timer = 0;
	}

}

void PlayState::updateTimer(const float &dt)
{
	timer += speed * dt;
}


void PlayState::render(sf::RenderTarget *target)
{
	this->matrix->render(target);
	this->matrix->renderBlockFigure(target,this->cur_figure);
}

void PlayState::endState()
{

}

void PlayState::generateFigure()
{
	int v = rand() % 7 + 1;
	delete this->cur_figure;

	this->cur_figure = new BlockFigure(*this->blockFigures[v]);

	int b = rand() % 256 + 1;
	this->cur_figure->setColor(sf::Color(0,0,b));
}






