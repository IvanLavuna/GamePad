//
// Created by ivan on 21.05.20.
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

#include "BlockFigure.h"

class Matrix
{
private:
	/// Initialisation
	void initMatrixVariables(uint height,uint width,sf::Vector2f size);
	void initView(sf::FloatRect flRect);
	void setView(sf::RenderWindow* window);

protected:
	/// variables
	uint height{};
	uint width{};
	uint blockWidth{};
	uint blockHeight{};

	/** change color in block or not**/
	bool** matrixArr;
	sf::Color** matrixArrColor;
	sf::VertexArray* lines;
	sf::View* view;

	/** block color **/
	sf::Color color;

public:
	Matrix(uint height, uint width, sf::FloatRect rectView,
		   sf::RenderWindow * window);

	virtual ~Matrix();

	/// render
	void renderMatrix(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
	void renderBlock(sf::RenderTarget* target,int i,int j);
	void renderBlockFigure(sf::RenderTarget* target,BlockFigure* figure);

	/// update
	void update(const float& dt);

	void showProjection();

	int getHeight() const{return this->height;}
	int getWidth() const { return this->width;}
	void stopFigure(BlockFigure* figure);

	bool canFall(BlockFigure* figure);
	void checkForRows();
	bool hasFirstRow();

	friend class BlockFigure;
};



#endif //GAMEPAD_MATRIX_H
