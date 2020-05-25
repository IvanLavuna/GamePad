//
// Created by ivan on 11.05.20.
//

#include "gui.h"



//// class	Button --------------------------------------------------

/// x,y = top left point
gui::Button::Button(float x, float y, float width, float height, std::string str, sf::Font* font,
			   sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor)
{
	///   colors
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	///   text
	this->font = font;
	this->text.setFont(*font);
	this->text.setString(str);
	this->text.setPosition(x,y);
	this->text.setFillColor(sf::Color(71,158,88));

	///   rectangle
	this->rect.setPosition(x,y);
	this->rect.setSize(sf::Vector2f(width,height+5));
	this->rect.setFillColor(idleColor);

	/// adjusting text according to rect using bin search
	std::function<int(int,int)> LambdaX = [&](int l,int r)
	{
		int mid = (l + r) / 2;
		this->text.setCharacterSize(mid);
		if(r > l)
		{
			if(this->text.getLocalBounds().width > width - 3)
				return LambdaX(l, mid);
			else
				return LambdaX(mid + 1,r);
		}
		else
			return mid;
	};
	LambdaX(0,1000);
	if((float)this->text.getCharacterSize() >= height)
		this->text.setCharacterSize((uint)height);
	std::function<int(int,int)> LambdaY = [&](int l,int r)
	{
		int mid = (l + r) / 2;
		this->text.setPosition((float)mid,this->text.getPosition().y);

		if(r > l)
		{
			if(this->text.getPosition().x - x > x+width - (this->text.getPosition().x + this->text.getLocalBounds().width))
				return LambdaY(l,mid);
			else
				return LambdaY(mid + 1,r);
		}
		else
			return mid;
	};
	LambdaY(x,x + width);
	std::function<int(int,int)> LambdaH = [&](int l,int r)
	{
		int mid = (l + r) / 2;
		this->text.setPosition(this->text.getPosition().x,float(mid));

		if(r > l)
		{
			if(this->text.getPosition().y - y > (y + height) - (this->text.getPosition().y + this->text.getGlobalBounds().height))
				return LambdaH(l,mid);
			else
				return LambdaH(mid + 1,r);
		}
		else
			return mid;
	};

}

gui::Button::~Button()
{
	delete font;
}

void gui::Button::setIdleColor()
{
	this->rect.setFillColor(this->idleColor);
}

void gui::Button::setHoverColor()
{
	this->rect.setFillColor(this->hoverColor);
}

void gui::Button::setActiveColor()
{
	this->rect.setFillColor(this->activeColor);
}

void gui::Button::update(sf::Vector2f mousePos)
{
	if(this->rect.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->setActiveColor();
		}
		else
		{
			this->setHoverColor();
		}
	}
	else
	{
		this->setIdleColor();
	}

}

void gui::Button::render(sf::RenderTarget *target)
{
	target->draw(this->rect);
	target->draw(this->text);
}

bool gui::Button::isPressed(sf::Vector2f mousePos)
{
	return this->rect.getGlobalBounds().contains(mousePos) &&
		   sf::Mouse::isButtonPressed(sf::Mouse::Left);
}



///// class GameBar -----------------------------------------------

/// constructors/destructor
gui::GameBar::GameBar(sf::Vector2u size) : renderText(true)
{
	/// init font
	this->font = new sf::Font();
	if(!this->font->loadFromFile("../Fonts/Amatic-Bold.ttf"))
	{
		std::cerr << "file ../Fonts/Amatic-Bold.ttf couldn't be opened" << "\n";
	}

	this->initButtons();
	this->initBackground(size);
	this->initText();
}

gui::GameBar::~GameBar()
{
	delete font;
	buttons.clear();
}

/// initialisation
void gui::GameBar::initButtons()
{
	buttons["home"] = new gui::Button(250,50,300,70," home ",this->font,
			sf::Color(124,190,228),sf::Color(92,142,171),
			sf::Color(41,67,81));
}

void gui::GameBar::initBackground(sf::Vector2u size)
{
	this->background.setPosition(0.f,0.f);
	this->background.setSize(sf::Vector2f(size));
	/// work with this a little bit later
	this->background.setFillColor(sf::Color(189,187,192));
}

void gui::GameBar::initText()
{
	this->text.setFont(*this->font);
	this->text.setPosition(120.f,250.f);
	this->text.setString("Push Enter to start playing");
	this->text.setCharacterSize(80);
	this->text.setFillColor(sf::Color(232,216,216));
}


/// update
void gui::GameBar::update(sf::Vector2f mousePosView, std::stack<State*>* states)
{
	this->updateButtons(mousePosView,states);
	this->updateEvents();
}

void gui::GameBar::updateButtons(sf::Vector2f mousePosView,std::stack<State*>* states)
{
	for(auto& item: this->buttons)
	{
		item.second->update(mousePosView);
	}

	if(buttons["home"]->isPressed(mousePosView))
	{
		states->pop();
	}

}



void gui::GameBar::updateEvents()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		this->renderText = false;


}

/// render
void gui::GameBar::render(sf::RenderTarget *target)
{
	target->draw(background);
	this->renderButtons(target);
	target->draw(text);
}

void gui::GameBar::renderButtons(sf::RenderTarget *target)
{
	for(auto& item: buttons)
		item.second->render(target);
}

bool gui::GameBar::isRenderingText() const
{
	return this->renderText;
}
















