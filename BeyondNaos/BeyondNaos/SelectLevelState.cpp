#include "SelectLevelState.h"
#include <iostream>
#include "Constants.h"

SelectLevelState::SelectLevelState(GameStateManager& gsm) :gsm(gsm), background("Resources/Backgrounds/landscape.gif", 1)
{
	background.setVector(-1, 0);
}

void SelectLevelState::Update(sf::RenderWindow * window, float frametime)
{
	background.Update();
}

void SelectLevelState::Draw(sf::RenderWindow * window)
{
	background.Draw(window);
	window->draw(selectLevelHeader);
	for (int i = 0; i < Options.size(); i++)
	{
		if (i == currentChoice)
		{
			Options.at(i)->setColor(sf::Color::Blue);
		}
		else
		{
			Options.at(i)->setColor(sf::Color::Black);
		}
		window->draw(*Options.at(i));
	}

	window->draw(pressEscapeMessage);
}

void SelectLevelState::Init() {
	bgSprite.setTexture(bg);
	bgSprite.setPosition(bgx, bgy);
	bgSprite.setScale(WINWIDTH*WINSCALE / bgSprite.getGlobalBounds().width, WINHEIGHT*WINSCALE / bgSprite.getGlobalBounds().height);
	if (!font.loadFromFile("Resources/Pixel.TTF")) {
		std::cout << "unable to load from file" << std::endl;
	}

	selectLevelHeader.setFont(font);
	selectLevelHeader.setString("SELECT LEVEL");
	selectLevelHeader.setCharacterSize(70);
	selectLevelHeader.setPosition(WINWIDTH*WINSCALE / 2 - selectLevelHeader.getGlobalBounds().width / 2, 80);
	selectLevelHeader.setColor(sf::Color(128, 0, 0));
	int offset = 80;
	for (sf::Text *t : Options)
	{
		t->setPosition((WINWIDTH*WINSCALE / 2 - t->getGlobalBounds().width / 2) - 50, 100 + offset);
		t->setColor(sf::Color(40, 40, 40));
		t->setCharacterSize(50);
		offset += 80;
	}

	pressEscapeMessage.setFont(font);
	pressEscapeMessage.setString("Press 'Esc' to view Main-Menu");
	pressEscapeMessage.setCharacterSize(50);
	pressEscapeMessage.setPosition((WINWIDTH*WINSCALE / 2 - selectLevelHeader.getGlobalBounds().width / 2) - 170, 560);
	pressEscapeMessage.setColor(sf::Color(255, 0, 0));

}

void SelectLevelState::KeyPressed(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Up)
	{
		currentChoice--;
		if (currentChoice < 0)
		{
			currentChoice = Options.size() - 1;
		}
	}
	if (key == sf::Keyboard::Down)
	{
		currentChoice++;
		if (currentChoice > Options.size() - 1)
		{
			currentChoice = 0;
		}
	}
	if (key == sf::Keyboard::Return)
	{
		selected();
	}

	if (key == sf::Keyboard::Escape)
	{
		gsm.SetState(GameStateManager::MENUSTATE);
		gsm.Init();
	}

}


void SelectLevelState::selected()
{
	if (currentChoice == 0)
	{
		gsm.SetState(GameStateManager::LEVEL1STATE);
		gsm.Init();
	}
	else if (currentChoice == 1)
	{
		//Leaderboard
		gsm.SetState(GameStateManager::LEVEL2STATE);
		gsm.Init();
	}
	else if (currentChoice == 2)
	{
		//Instruction State
		gsm.SetState(GameStateManager::LEVEL3STATE);
		gsm.Init();

	}

}