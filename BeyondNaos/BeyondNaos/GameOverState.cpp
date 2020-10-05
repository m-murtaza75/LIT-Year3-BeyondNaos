#include "GameOverState.h"
#include <iostream>
#include "Constants.h"

GameOverState::GameOverState(GameStateManager& gsm) :gsm(gsm), background("Resources/Backgrounds/landscape.gif", 1)
{
	background.setVector(-1, 0);
}

void GameOverState::Update(sf::RenderWindow * window, float frametime)
{
	background.Update();
}

void GameOverState::Draw(sf::RenderWindow * window)
{
	background.Draw(window);
	window->draw(GameOverHeader);
	window->draw(pressEnterMessage);
	window->draw(pressEscapeMessage);
	window->draw(playerScoreMessage);

}

void GameOverState::Init() 
{
	bgSprite.setTexture(bg);
	bgSprite.setPosition(bgx, bgy);
	bgSprite.setScale(WINWIDTH*WINSCALE / bgSprite.getGlobalBounds().width, WINHEIGHT*WINSCALE / bgSprite.getGlobalBounds().height);
	if (!font.loadFromFile("Resources/GOTHIC.TTF")) 
	{
		std::cout << "unable to load from file" << std::endl;
	}


	GameOverHeader.setFont(font);
	GameOverHeader.setString("GAME OVER");
	GameOverHeader.setCharacterSize(110);
	GameOverHeader.setPosition(WINWIDTH*WINSCALE / 2 - GameOverHeader.getGlobalBounds().width / 2, 120);
	GameOverHeader.setColor(sf::Color(255, 0, 0));

	playerScore = getLastScore();

	playerScoreMessage.setFont(font);
	playerScoreMessage.setString("Your Score: " + playerScore);
	playerScoreMessage.setCharacterSize(50);
	playerScoreMessage.setPosition(WINWIDTH*WINSCALE / 2 - GameOverHeader.getGlobalBounds().width / 2, 320);
	playerScoreMessage.setColor(sf::Color(255, 0, 0));


	pressEnterMessage.setFont(font);
	pressEnterMessage.setString("Press 'Enter' to Play-Again");
	pressEnterMessage.setCharacterSize(50);
	pressEnterMessage.setPosition(WINWIDTH*WINSCALE / 2 - GameOverHeader.getGlobalBounds().width / 2, 440);
	pressEnterMessage.setColor(sf::Color(255, 0, 0));

	pressEscapeMessage.setFont(font);
	pressEscapeMessage.setString("Press 'Esc' to view Main-Menu");
	pressEscapeMessage.setCharacterSize(50);
	pressEscapeMessage.setPosition(WINWIDTH*WINSCALE / 2 - GameOverHeader.getGlobalBounds().width / 2, 560);
	pressEscapeMessage.setColor(sf::Color(255, 0, 0));




}

void GameOverState::KeyPressed(sf::Keyboard::Key key)
{

	if (key == sf::Keyboard::Return)
	{
		
		gsm.SetState(GameStateManager::SELECTLEVEL);
		gsm.Init();
	}

	if (key == sf::Keyboard::Escape)
	{
		gsm.SetState(GameStateManager::MENUSTATE);
		gsm.Init();
	}

}

std::string GameOverState::getLastScore()
{
	std::string score;

	std::fstream fin("Resources/gameData/scores.txt");

	//fin.seekg(-2, std::ios::end);                // go to one spot before the EOF

	while (!fin.eof())
	{
		fin >> score;
	}
		
	fin.close();

	std::ofstream outputFile("Resources/gameData/tempScore.txt");
	outputFile << 0 << std::endl;
	outputFile.close();

	return score;

}