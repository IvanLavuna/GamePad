//
// Created by ivan on 23.05.20.
//

#include "BlockFigure.h"

#include <utility>

BlockFigure::BlockFigure(std::vector<std::pair<int,int>> figure, sf::Color color):
	figure(std::move(figure)), color(color), timer(0),isFallen(true)
{

}

BlockFigure::~BlockFigure()
{

}

void BlockFigure::moveLeft(const float& dt)
{
	for(auto& item: figure)
		item.first -= 1;
}

void BlockFigure::moveRight(const float& dt)
{
	for (auto &item: figure)
		item.first += 1;
}

void BlockFigure::moveDown(const float& dt)
{
	for(auto& item: figure)
		item.second += 1;
}

void BlockFigure::LandDown(Matrix* matrix)
{

}

int BlockFigure::getLeftMostCoordinate()
{
	int lmc = 1000;
	for(auto& item: this->figure)
		lmc = std::min(lmc,item.first);
	return lmc;
}

int BlockFigure::getRightMostCoordinate()
{
	int rmc = -1000;
	for(auto& item: this->figure)
		rmc = std::max(rmc,item.first);
	return rmc;
}

int BlockFigure::getBottomMostCoordinate()
{
	int bmc = -1000;
	for(auto& item: this->figure)
		bmc = std::max(bmc,item.second);
	return bmc;
}

void BlockFigure::setPosition(int x,int y)
{

}

void BlockFigure::fall(const float& dt)
{

	if(this->timer > 50 && isFallen)
	{
		this->moveDown(dt);
		this->timer = 0;
	}
}

void BlockFigure::updateTimer(const float& speed, const float& dt)
{
	timer += speed * dt;
}

void BlockFigure::RotateLeft()
{
	std::pair<int,int> center = this->figure[0];
	for(auto& item: figure)
	{
		item.first -= center.first;
		item.second -= center.second;
	}
	for(auto & item: figure)
	{
		float temp = item.first;
		item.first = item.second;
		item.second = -temp;
	}
	for(auto& item: figure)
	{
		item.first += center.first;
		item.second += center.second;
	}
}

void BlockFigure::RotateRight()
{

}

void BlockFigure::checkCoordinatesForFalling(int height)
{
	if(getBottomMostCoordinate() >= height - 1 )
	{
		this->isFallen = false;
	}


}
