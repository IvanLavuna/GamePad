//
// Created by ivan on 18.05.20.
//

#include "MainMenuState.h"

/// constructors/destructor
MainMenuState::MainMenuState(sf::RenderWindow* window,std::stack<State*>* states):
	State(window,states)
{
	this->initFonts();
	this->initButtons();
	this->initGameText();
	this->initBackground(window);
	this->initAnimations();
}

MainMenuState::~MainMenuState()
{
	delete burstAnim;
	delete this->font;
	buttons.clear();
}

/// Initialisation
void MainMenuState::initFonts()
{
	font = new sf::Font();
	if(!font->loadFromFile("../Fonts/Amatic-Bold.ttf"))
	{
		std::cerr << "File in /Fonts/Amatic-Bold.ttf can not be opened." << "\n";
	}
}

/** 3 buttons
 	  "play"     button
 	  "settings" button
 	  "exit"     button **/
void MainMenuState::initButtons()
{
	buttons["play"] = new gui::Button(50,320,140,40,"play",this->font,
			sf::Color(124,190,228),sf::Color(92,142,171),
			sf::Color(41,67,81));
	buttons["settings"] = new gui::Button(50,400,140,40,"settings",this->font,
								 sf::Color(124,190,228),sf::Color(92,142,171),
								 sf::Color(41,67,81));
	buttons["exit"] = new gui::Button(50,480,140,40,"exit",this->font,
									 sf::Color(124,190,228),sf::Color(92,142,171),
									 sf::Color(41,67,81));}

void MainMenuState::initGameText()
{
	this->gameText.setFont(*this->font);
	this->gameText.setString("Old School");
	this->gameText.setCharacterSize(120);
	this->gameText.setPosition(50.f,50.f);
	this->gameText.setFillColor(sf::Color(36,39,40));
	this->gameText.setOutlineThickness(2.f);
	this->gameText.setOutlineColor(sf::Color(23,24,24));
}

void MainMenuState::initBackground(sf::RenderWindow* window)
{
	this->background.setPosition(0.f,0.f);
	this->background.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
	this->background.setFillColor(sf::Color(189,187,192));
}

void MainMenuState::initAnimations()
{
	burstAnim = new BurstAnimation(500,400);
}


/// functions
void MainMenuState::endState()
{

}

/// update
void MainMenuState::updateButtons()
{
	for(auto item: this->buttons)
	{
		item.second->update(sf::Vector2f(this->mousePosView));
	}

	/// new game
	if(this->buttons["play"]->isPressed(this->mousePosView))
	{
		this->states->push(new GameState(this->window,this->states));
	}
}

void MainMenuState::updateInput(const float &dt)
{

}

void MainMenuState::update(const float &dt)
{
	this->updateMousePositions();
	this->updateButtons();
	this->updateAnimations();
}

void MainMenuState::updateAnimations()
{
	burstAnim->update();
}

/// render
void MainMenuState::render(sf::RenderTarget *target)
{
	target->draw(background);
	target->draw(this->gameText);
	this->renderButtons(target);
	this->burstAnim->render(target);
}

void MainMenuState::renderButtons(sf::RenderTarget *target)
{
	for(auto& item: this->buttons)
		item.second->render(target);
}








