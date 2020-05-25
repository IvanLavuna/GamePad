//
// Created by ivan on 19.05.20.
//

#ifndef GAMEPAD_ANIMATION_H
#define GAMEPAD_ANIMATION_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
private:

protected:
	sf::Texture* texture;
	sf::Sprite sprite;

	float blockWidth{};
	float blockHeight{};
	uint height{};
	uint width{};

	uint curPosX;
	uint curPosY;

	/// Initialisation
	void initSize(float blockWidth = 0, float blockHeight = 0, uint height = 0, uint width = 0);
	void initTexture(std::string fileName);
public:
	explicit Animation(std::string textureFile, uint height, uint width,float posX,float posY);
	virtual ~Animation();

	virtual void renderFragment(sf::RenderTarget *target = nullptr);
	virtual void render(sf::RenderTarget* target = nullptr);

	virtual void update();

};


#endif //GAMEPAD_ANIMATION_H
