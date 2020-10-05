#include "InstructionState.h"
#include <iostream>
#include "Constants.h"

InstructionState::InstructionState(GameStateManager& gsm) :gsm(gsm), background("Resources/Backgrounds/Instructions.jpg", 1)
{
	background.setVector(-1, 0);
}

void InstructionState::Update(sf::RenderWindow * window, float frametime)
{
	/*background.Update();*/
}

void InstructionState::Draw(sf::RenderWindow * window)
{
	background.Draw(window);
	window->draw(instructionHeader);
	window->draw(pressEnterMessage);

}

void InstructionState::Init()
{
	bgSprite.setTexture(bg);
	bgSprite.setPosition(bgx, bgy);
	bgSprite.setScale(WINWIDTH*WINSCALE / bgSprite.getGlobalBounds().width, WINHEIGHT*WINSCALE / bgSprite.getGlobalBounds().height);
	if (!font.loadFromFile("Resources/Pixel.TTF"))
	{
		std::cout << "unable to load from file" << std::endl;
	}


	instructionHeader.setFont(font);
	instructionHeader.setString("How to Play");
	instructionHeader.setCharacterSize(40);
	instructionHeader.setPosition(WINWIDTH*WINSCALE / 2 - instructionHeader.getGlobalBounds().width / 4, 10);
	instructionHeader.setColor(sf::Color(255, 0, 0));


	pressEnterMessage.setFont(font);
	pressEnterMessage.setString("Press 'Backspace'to return to the Main Menu ");
	pressEnterMessage.setCharacterSize(20);
	pressEnterMessage.setPosition(WINWIDTH*WINSCALE / 2 - instructionHeader.getGlobalBounds().width / 4, 600);
	pressEnterMessage.setColor(sf::Color(255, 0, 0));




}

void InstructionState::KeyPressed(sf::Keyboard::Key key)
{

	if (key == sf::Keyboard::BackSpace)
	{

		gsm.SetState(GameStateManager::MENUSTATE);
		//GameStateManager gsm;
		gsm.Init();
	}

}



