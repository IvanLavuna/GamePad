//
// Created by ivan on 25.05.20.
//
///		  1 2 3 4 5 6 7 8 ...
/// 	  -------------------------------> x
///	    1|
///		2|
///		3|
///		4|
///		5|
///		6|
///		7|
///		8|
///		 y
#ifndef GAMEPAD_MATRIX_H
#define GAMEPAD_MATRIX_H

#include "Tetramino.h"

class Matrix
{
private:
	friend class Tetromino;

	/// variables
	uint height;
	uint width;
	uint blockWidth;
	uint blockHeight;

	bool** matrixArr;	/** change color in block or not **/
	sf::Color** matrixArrColor;
	sf::VertexArray* lines;

	sf::Color color;

	/// initialisation
	void initMatrix(sf::Vector2u windowSize);

public:
	explicit Matrix(sf::Vector2u windowSize, uint height = 20, uint width = 10,
			sf::Color matrixColor = sf::Color(84,238,217));
	~Matrix();

	/// render
	void renderLines(sf::RenderWindow* window);
	void renderMatrix(sf::RenderWindow* window);
	void renderTetromino(sf::RenderWindow* window,Tetromino* tetromino);
	void renderProjection(sf::RenderWindow* window,Tetromino* tetromino);
	void renderBlock(sf::RenderWindow* window,int i,int j,sf::Color blockColor = sf::Color(225,224,205)) const;

	/// core
	void burnLine(int line);
	void checkLines(); /** checks all matrix for full line **/
	sf::Color getColor(){return this->color;}
	void engrave(Tetromino* tetromino);
	bool checkFirstLine();
	int getHeight() const{ return this->height;}
	int getWidth() const{ return this->width;}

};




#endif //GAMEPAD_MATRIX_H
