//
// Created by ivan on 18.05.20.
//

#ifndef GAMEPAD_ENTITY_H
#define GAMEPAD_ENTITY_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Entity
{
private:

protected:
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	/// Functions

	/// maybe dt must be in paramneters
	virtual void move(const float& dt,float dir_x,float dir_y) = 0;
	virtual void update( const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void updateInput(const float& dt) = 0;

};


#endif //GAMEPAD_ENTITY_H
