//
// Created by ivan on 21.05.20.
//

#include "Matrix.h"


Matrix::Matrix(uint height, uint width, sf::FloatRect rectView,
		sf::RenderWindow * window)
{
	this->initView(rectView);
	this->setView(window);
	this->initMatrixVariables(height, width,this->view->getSize());
}

Matrix::~Matrix()
{
	for (int i = 0; i < this->width; ++i)
		delete [] matrixArrColor[i];
	delete [] matrixArrColor;

	for (int i = 0; i < this->width; ++i)
		delete [] matrixArr[i];
	delete [] matrixArr;

	delete [] lines;
	delete  view;
}

/// Initialisation
void Matrix::initMatrixVariables(uint height, uint width, sf::Vector2f size)
{
	this->height = height;
	this->width = width;
	this->blockHeight = size.x / height;
	this->blockWidth = size.y / width;

	/// lines
	this->lines = new sf::VertexArray();

	lines->setPrimitiveType(sf::Lines);
	for (int i = 0; i < height; ++i)
	{
		sf::Vertex vertex1(sf::Vector2f(0,i * blockHeight));
		sf::Vertex vertex2(sf::Vector2f(this->view->getSize().x, i * blockHeight));
		vertex1.color = sf::Color(89,118,114);
		vertex2.color = sf::Color(60,94,89);
		lines->append(vertex1);
		lines->append(vertex2);
	}
	for (int i = 0; i < width; ++i)
	{
		sf::Vertex vertex1(sf::Vector2f(i * blockWidth,0));
		sf::Vertex vertex2(sf::Vector2f(i * blockWidth, this->view->getSize().y));
		vertex1.color = sf::Color(89,118,114);
		vertex2.color = sf::Color(60,94,89);
		lines->append(vertex1);
		lines->append(vertex2);
	}

	/// color : default color is sf::Color(136,201,199)
	this->color = sf::Color(136,201,199);

	matrixArrColor = new sf::Color*[width];
	for (int j = 0; j < width; ++j)
		matrixArrColor[j] = new sf::Color[height];
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
			matrixArrColor[i][j] = this->color;
	}

	/// matrix Array
	matrixArr = new bool*[width];
	for (int j = 0; j < width; ++j)
		matrixArr[j] = new bool[height];
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
			matrixArr[i][j] = false;
	}

}

void Matrix::initView(sf::FloatRect flRect)
{
	this->view = new sf::View();
	this->view->setViewport(flRect);
}

void Matrix::setView(sf::RenderWindow* window)
{
	window->setView(*this->view);
}

/// render
void Matrix::render(sf::RenderTarget *target)
{
	this->renderMatrix(target);
}

void Matrix::renderMatrix(sf::RenderTarget *target)
{
	for(int i = 0; i < width;i++)
	{
		for (int j = 0; j < height; ++j)
		{
			if(matrixArr[i][j])
				this->renderBlock(target, i, j);
			else
			{
				sf::RectangleShape shape(sf::Vector2f(blockWidth,blockHeight));
				shape.setFillColor(this->color);
				shape.setPosition(float(i) * blockWidth,float(j) * blockHeight);
				target->draw(shape);
			}
		}
	}
	target->draw(*lines);
}

void Matrix::renderBlock(sf::RenderTarget* target, int i, int j)
{
	sf::RectangleShape shape(sf::Vector2f(blockWidth,blockHeight));
	shape.setFillColor(this->matrixArrColor[i][j]);
	shape.setPosition(float(i) * blockWidth,float(j) * blockHeight);
	target->draw(shape);
}

void Matrix::renderBlockFigure(sf::RenderTarget* target,BlockFigure *figure)
{
	for(auto& item : figure->figure)
	{
		sf::RectangleShape shape(sf::Vector2f(blockWidth,blockHeight));
		shape.setFillColor(figure->color);
		shape.setPosition(float(item.first) * blockWidth,float(item.second) * blockHeight);
		target->draw(shape);
	}
}

void Matrix::stopFigure(BlockFigure* figure)
{
	for(auto& item : figure->figure)
	{
		this->matrixArr[item.first][item.second] = true;
		this->matrixArrColor[item.first][item.second] = figure->color;
	}
}

void Matrix::update(const float &dt)
{

}

void Matrix::showProjection()
{

}

bool Matrix::canFall(BlockFigure* figure)
{
	for(auto item : figure->figure)
	{
		if(matrixArr[item.first][item.second + 1])
			return false;
	}
	return true;
}

void Matrix::checkForRows()
{
	for(int i = 0; i < height;i++)
	{
		bool a = true;
		for (int j = 0; j < width; ++j)
		{
			a = a && matrixArr[j][i];
		}
		if(a)
		{
			for(int j = i; j > 0; j--)
			{
				for(int k = 0; k < width; k++)
				{
					matrixArr[k][j] = matrixArr[k][j - 1];
					matrixArrColor[k][j] = matrixArrColor[k][j - 1];
				}
			}
		}
	}
}

bool Matrix::hasFirstRow()
{
	for(int i = 0; i < width; i++)
	{
		if(this->matrixArr[i][0] == true)
			return true;
	}
	return false;
}


/// update





