//
// Created by ivan on 19.05.20.
//

#include "Animation.h"

/// constructors/destructors
Animation::Animation(std::string textureFile, uint height, uint width,float posX,float posY):
		curPosX(1),curPosY(1)
{
	initTexture(textureFile);
	initSize(this->texture->getSize().x/float(width),this->texture->getSize().y/float(height),height,width);


	this->sprite.setPosition(posX,posY);
	this->sprite.setScale(2.f,2.f);
	this->sprite.setTexture(*this->texture);
	this->sprite.setTextureRect(sf::IntRect(0,0, this->blockWidth, this->blockHeight));

}

Animation::~Animation()
{
	delete texture;
}

void Animation::initSize(float blWidth, float blHeight, uint h, uint w)
{
	this->blockWidth = blWidth;
	this->blockHeight = blHeight;
	this->height = h;
	this->width = w;
}

void Animation::initTexture(std::string fileName)
{
	this->texture = new sf::Texture();
	if(!this->texture->loadFromFile(fileName))
	{
		std::cerr << "File " << fileName << " couldn't be opened." << std::endl;
	}

}

void Animation::update()
{
	if(this->curPosY == this->height && this->curPosX == this->width)
	{
		this->curPosX = 1;
		this->curPosY = 1;
	}
	else if(this->curPosX == this->width)
	{
		this->curPosY++;
		this->curPosX = 1;
	}
	else
	{
		this->curPosX++;
	}
	sprite.setTextureRect(sf::IntRect((curPosX - 1)*blockWidth,(curPosY - 1)*blockHeight,blockWidth,blockHeight));


}

void Animation::render(sf::RenderTarget *target)
{
	this->renderFragment(target);
}

void Animation::renderFragment(sf::RenderTarget *target)
{
	target->draw(sprite);
}
