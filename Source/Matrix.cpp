//
// Created by ivan on 25.05.20.
//

#include "Matrix.h"

/// constructors/destructor
Matrix::Matrix(sf::Vector2u windowSize, uint height, uint width, sf::Color matrixColor) :
	height(height), width(width), color(matrixColor)
{
	this->initMatrix(windowSize);
}
Matrix::~Matrix()
{
	for (int i = 0; i < this->height; ++i)
		delete [] matrixArr[i];
	delete [] matrixArr;

	for (int i = 0; i < this->height; ++i)
		delete [] matrixArrColor[i];
	delete [] matrixArrColor;

	delete [] lines;
}

/// initialisation
void Matrix::initMatrix(sf::Vector2u windowSize)
{
	this->blockHeight = windowSize.y / height;
	this->blockWidth = windowSize.x / width;

	/// lines
	this->lines = new sf::VertexArray();

	lines->setPrimitiveType(sf::Lines);
	for (int i = 0; i <= height; ++i)
	{
		sf::Vertex vertex1(sf::Vector2f(0,i * blockHeight));
		sf::Vertex vertex2(sf::Vector2f(windowSize.x, i * blockHeight));
		vertex1.color = sf::Color(89,118,114);
		vertex2.color = sf::Color(60,94,89);
		lines->append(vertex1);
		lines->append(vertex2);
	}
	for (int i = 0; i <= width; ++i)
	{
		sf::Vertex vertex1(sf::Vector2f(i * blockWidth,0));
		sf::Vertex vertex2(sf::Vector2f(i * blockWidth, windowSize.y));
		vertex1.color = sf::Color(89,118,114);
		vertex2.color = sf::Color(60,94,89);
		lines->append(vertex1);
		lines->append(vertex2);
	}

	/// matrix
	this->matrixArr = new bool*[width];
	for (int i = 0; i < width; ++i)
		matrixArr[i] = new bool[height];

	for (int i = 0; i < this->width; ++i)
	{
		for (int j = 0; j < this->height; ++j)
			matrixArr[i][j] = false;
	}

	/// filling borders
	for(int i = 0; i < this->width; i++)
		matrixArr[i][this->height - 1] = true;
	for (int i = 0; i < this->height; ++i)
	{
		matrixArr[0][i] = true;
		matrixArr[this->width - 1][i] = true;
	}

	/// matrix arr color
	matrixArrColor = new sf::Color*[width];
	for (int j = 0; j < width; ++j)
		matrixArrColor[j] = new sf::Color[height];
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
			matrixArrColor[i][j] = this->color;
	}
}

void Matrix::renderLines(sf::RenderWindow *window)
{
	window->draw(*this->lines);
}

void Matrix::renderMatrix(sf::RenderWindow *window)
{
	for(int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; ++j)
		{
			if(this->matrixArr[i][j])
			{
				this->renderBlock(window,i,j,matrixArrColor[i][j]);
			}
		}
	}
}

void Matrix::renderTetromino(sf::RenderWindow *window, Tetromino *tetromino)
{
	for(auto& item : tetromino->figure)
	{
		this->renderBlock(window,item.first,item.second,tetromino->color);
	}
}

void Matrix::renderProjection(sf::RenderWindow *window, Tetromino *tetromino)
{
	int i = 0;
	bool ok = true;
	while(ok)
	{
		for(auto& item : tetromino->figure)
		{
			if(this->matrixArr[item.first][item.second + i])
			{
				ok = false;
				i -= 2;
				break;
			}
		}
		i++;
	}
	/// add projection color if you want
	/// default projection color is sf::Color(245,243,188)
	for(auto& item: tetromino->figure)
	{
		renderBlock(window,item.first,item.second + i,sf::Color(245,243,188));
	}
}

void Matrix::renderBlock(sf::RenderWindow *window, int i, int j, sf::Color blockColor) const
{
	sf::RectangleShape shape(sf::Vector2f(blockWidth,blockHeight));
	shape.setFillColor(blockColor);
	shape.setPosition(float(i) * blockWidth,float(j) * blockHeight);
	window->draw(shape);
}

void Matrix::burnLine(int line)
{
	/// short animation maybe
	for (int i = line; i > 0; --i)
	{
		for (int j = 0; j < width; ++j)
		{
			matrixArr[j][i] = matrixArr[j][i - 1];
		}
	}
}

void Matrix::checkLines()
{
	for (int i = 0; i < this->height - 1; ++i)
	{
		bool isBurn = true;
		for (int j = 1; j < this->width - 1; ++j)
		{
			if(!matrixArr[j][i])
			{
				isBurn = false;
				break;
			}
		}
		if(isBurn)
			this->burnLine(i);
	}
}

void Matrix::engrave(Tetromino *tetromino)
{
	for(auto& item: tetromino->figure)
	{
		this->matrixArr[item.first][item.second] = true;
		this->matrixArrColor[item.first][item.second] = tetromino->color;
	}
}

bool Matrix::checkFirstLine()
{
	for(int i = 1;i < width - 1;i ++)
	{
		if(this->matrixArr[i][0])
			return true;
	}
	return false;
}





