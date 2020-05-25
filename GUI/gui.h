//
// Created by ivan on 20.05.20.
//

#ifndef GAMEPAD_GUI_H
#define GAMEPAD_GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "State.h"
namespace gui
{

	class Button
	{
	private:
		/// variables
		sf::Text text;
		sf::Font* font;
		sf::RectangleShape rect;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

	public:

		Button(float x, float y, float width, float height, std::string str, sf::Font* font,
			   sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor);
		~Button();

		void setIdleColor();
		void setHoverColor();
		void setActiveColor();

		void update(sf::Vector2f mousePos);
		void render(sf::RenderTarget* target = nullptr);

		bool isPressed(sf::Vector2f mousePos);

	};

	/** poor imagination says me that Game Bar only has buttons and background **/

	class GameBar
	{
	private:
		std::map<std::string,Button*> buttons;
		sf::RectangleShape background;
		sf::Font* font;

		/** touch to start playing **/
		sf::Text text;
		bool renderText; /// if text is not rendering go to PlayState

		/// initialisation
		void initButtons();
		void initBackground(sf::Vector2u size);
		void initText();
	public:
		explicit GameBar(sf::Vector2u size);
		~GameBar();

		/// update
		void update(sf::Vector2f mousePosView,std::stack<State*>* states);
		void updateButtons(sf::Vector2f mousePos,std::stack<State*>* states);
		void updateEvents();

		/// render
		void render(sf::RenderTarget* target = nullptr);
		void renderButtons(sf::RenderTarget* target = nullptr);

		bool isRenderingText() const;
		void setRenderState(bool state = true){ this->renderText = state;}
	};

}


#endif //GAMEPAD_GUI_H
