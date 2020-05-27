//
// Created by ivan on 25.05.20.
//

#ifndef GAMEPAD_TETRAMINO_H
#define GAMEPAD_TETRAMINO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class Matrix;
enum TetrominoType
{
	FIRSTTETROMINO = 0,
	SECONTETROMINO,
	THIRDTETROMINO,
	FOURTHTETROMINO,
	FIFTHTETROMINO,
	SIXTHTETROMINO,
	SEVENTHTETROMINO
};


/** Tetromino class widely cooperates with Matrix class **/

class Tetromino
{
	friend class Matrix;
private:
	/// variables
	/** first position is origin**/
	std::vector<std::pair<int,int>> figure;
	sf::Color color;

	/** timer is nearly for fall function **/
	float timer;
	float speed;

public:
	explicit Tetromino(TetrominoType type, sf::Color color = sf::Color(100,202,93), float speed = 20);
	~Tetromino();

	void moveLeft();
	void moveRight();
	void moveDown();
	void RotateRight();
	void RotateLeft();
	void fall(const float& dt);
	void LandDown(Matrix* matrix);

	void updateTimer(const float& dt);

	int getLeftMostCoordinate();
	int getRightMostCoordinate();
	int getBottomMostCoordinate();
	/** origin - place of center**/
	std::pair<int,int> getOrigin();

	/** set the position of the origin **/
	void setPosition(int x,int y);
	bool canFall(Matrix* matrix);
	bool canMoveRight(Matrix* matrix);
	bool canMoveLeft(Matrix* matrix);
	void setColor(sf::Color Color){this->color = Color;}

};


#endif //GAMEPAD_TETRAMINO_H
