#include "GameCompletionState.h"
#include <iostream>
#include "Constants.h"

GameCompletionState::GameCompletionState(GameStateManager& gsm) :gsm(gsm), background("Resources/Backgrounds/landscape.gif", 1)
{
	background.setVector(-1, 0);
}

void GameCompletionState::Update(sf::RenderWindow * window, float frametime)
{
	background.Update();
}

void GameCompletionState::Draw(sf::RenderWindow * window)
{
	background.Draw(window);
	window->draw(GameCompletionHeader);
	window->draw(pressEnterMessage);
	window->draw(pressEscapeMessage);
	window->draw(playerScoreMessage);

}

void GameCompletionState::Init()
{
	bgSprite.setTexture(bg);
	bgSprite.setPosition(bgx, bgy);
	bgSprite.setScale(WINWIDTH*WINSCALE / bgSprite.getGlobalBounds().width, WINHEIGHT*WINSCALE / bgSprite.getGlobalBounds().height);
	if (!font.loadFromFile("Resources/GOTHIC.TTF"))
	{
		std::cout << "unable to load from file" << std::endl;
	}


	GameCompletionHeader.setFont(font);
	GameCompletionHeader.setString("Congratulations!\n \tYOU WIN!");
	GameCompletionHeader.setCharacterSize(90);
	GameCompletionHeader.setPosition(WINWIDTH*WINSCALE / 2 - GameCompletionHeader.getGlobalBounds().width / 2, 60);
	GameCompletionHeader.setColor(sf::Color(255, 0, 0));

	playerScore = getLastScore();

	playerScoreMessage.setFont(font);
	playerScoreMessage.setString("Your Score: " + playerScore);
	playerScoreMessage.setCharacterSize(50);
	playerScoreMessage.setPosition(WINWIDTH*WINSCALE / 2 - GameCompletionHeader.getGlobalBounds().width / 2, 320);
	playerScoreMessage.setColor(sf::Color(255, 0, 0));


	pressEnterMessage.setFont(font);
	pressEnterMessage.setString("Press 'Enter' to Play-Again");
	pressEnterMessage.setCharacterSize(50);
	pressEnterMessage.setPosition(WINWIDTH*WINSCALE / 2 - GameCompletionHeader.getGlobalBounds().width / 2, 440);
	pressEnterMessage.setColor(sf::Color(255, 0, 0));

	pressEscapeMessage.setFont(font);
	pressEscapeMessage.setString("Press 'Esc' to view Main-Menu");
	pressEscapeMessage.setCharacterSize(50);
	pressEscapeMessage.setPosition(WINWIDTH*WINSCALE / 2 - GameCompletionHeader.getGlobalBounds().width / 2, 560);
	pressEscapeMessage.setColor(sf::Color(255, 0, 0));




}

void GameCompletionState::KeyPressed(sf::Keyboard::Key key)
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

std::string GameCompletionState::getLastScore()
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