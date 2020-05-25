//
// Created by ivan on 23.05.20.
//

#ifndef GAMEPAD_BLOCKFIGURE_H
#define GAMEPAD_BLOCKFIGURE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Matrix;

class BlockFigure
{
private:
	/// variables
	std::vector<std::pair<int,int>> figure;
	sf::Color color;
	float timer;
	bool isFallen;

public:
	BlockFigure(std::vector<std::pair<int,int>> figure, sf::Color color);
	~BlockFigure();

	void updateTimer(const float& speed, const float& dt);
	int getLeftMostCoordinate();
	int getRightMostCoordinate();
	int getBottomMostCoordinate();
	void moveLeft(const float& dt);
	void moveRight(const float& dt);
	void moveDown(const float& dt);
	void LandDown(Matrix* matrix);
	void RotateLeft();
	void RotateRight();
	void setPosition(int x,int y);
	void fall(const float& dt);
	void checkCoordinatesForFalling(int height);
	bool Fallen() const { return isFallen;}
	bool setColor(sf::Color color){this->color = color;};
	friend class Matrix;
};


#endif //GAMEPAD_BLOCKFIGURE_H
