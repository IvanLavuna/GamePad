//
// Created by ivan on 25.05.20.
//

#include "Tetramino.h"
#include "Matrix.h"

Tetromino::Tetromino(TetrominoType type, sf::Color color,float speed) :
	color(color), timer(0), speed(speed)
{
	switch(type)
	{
		case FIRSTTETROMINO:
			this->figure = { {2,0},{0,0}, {1,0}, {3,0}};
			break;
		case SECONTETROMINO:
			this->figure = {{1,1}, {0,0}, {0,1}, {2,1}};
			break;
		case THIRDTETROMINO:
			this->figure = {  {1,1},{0,1},{2,1}, {2,0}};
			break;
		case FOURTHTETROMINO:
			this->figure =  { {0,0}, {0,1},{1,0}, {1,1}};
			break;
		case FIFTHTETROMINO:
			this->figure = { {1,1},{0,1},{1,0}, {2,0}};
			break;
		case SIXTHTETROMINO:
			this->figure = {  {1,1},{0,1},{2,1}, {1,0}};
			break;
		case SEVENTHTETROMINO:
			this->figure = { {1,1},{0,0}, {1,0}, {2,1}};
			break;
	}
}

Tetromino::~Tetromino()
{

}

/// moving
void Tetromino::moveLeft()
{
	for(auto& item: this->figure)
		item.first -= 1;
}

void Tetromino::moveRight()
{
	for (auto &item: this->figure)
		item.first += 1;
}

void Tetromino::moveDown()
{
	for(auto& item: this->figure)
		item.second += 1;
}

void Tetromino::RotateRight()
{
	std::pair<int,int> origin = this->getOrigin();
	for(auto& item: figure)
	{
		item.first -= origin.first;
		item.second -= origin.second;
		int temp = item.first;
		item.first = (item.second + origin.first);
		item.second = (-temp + origin.second);
	}

}

void Tetromino::RotateLeft()
{
	std::pair<int,int> origin = this->getOrigin();
	for(auto& item: figure)
	{
		item.first -= origin.first;
		item.second -= origin.second;
		int temp = item.first;
		item.first = (-item.second + origin.first);
		item.second = (temp + origin.second);
	}
}

void Tetromino::fall(const float &dt)
{
	if(timer * speed  >= 10)
	{
		this->moveDown();
		timer = 0;
	}
}

void Tetromino::LandDown(Matrix *matrix)
{
	int i = 0;
	bool ok = true;
	while(ok)
	{
		for(auto& item : this->figure)
		{
			if(matrix->matrixArr[item.first][item.second + i])
			{
				ok = false;
				i -= 2;
				break;
			}
		}
		i++;
	}

	for(auto& item: this->figure)
		item.second += i;
}

/// update
void Tetromino::updateTimer(const float &dt)
{
	/** don't actually know if it is smart what i do here **/
	this->timer += dt;
}

/// get
int Tetromino::getLeftMostCoordinate()
{
	int lmc = 100000;
	for(auto& item: this->figure)
		lmc = std::min(lmc,item.first);
	return lmc;
}

int Tetromino::getRightMostCoordinate()
{
	int rmc = -100000;
	for(auto& item: this->figure)
		rmc = std::max(rmc,item.first);
	return rmc;}

int Tetromino::getBottomMostCoordinate()
{
	int bmc = -100000;
	for(auto& item: this->figure)
		bmc = std::max(bmc,item.second);
	return bmc;
}

std::pair<int, int> Tetromino::getOrigin()
{
	return figure[0];
}

/// set
/** set the position of the origin **/
void Tetromino::setPosition(int x, int y)
{
	std::pair<int,int> origin = this->getOrigin();
	int dx = x - origin.first, dy = y - origin.second;
	for(auto& item: this->figure)
	{
		item.first += dx;
		item.second += dy;
	}
}

bool Tetromino::canFall(Matrix *matrix)
{
	for(auto& item : this->figure)
	{
		if(matrix->matrixArr[item.first][item.second + 1])
			return false;
	}
	return true;
}

bool Tetromino::canMoveRight(Matrix *matrix)
{
	for(auto& item: this->figure)
	{
		if(matrix->matrixArr[item.first + 1][item.second])
			return false;
	}
	return true;
}

bool Tetromino::canMoveLeft(Matrix *matrix)
{
	for(auto& item: this->figure)
	{
		if(matrix->matrixArr[item.first - 1][item.second])
			return false;
	}
	return true;
}







