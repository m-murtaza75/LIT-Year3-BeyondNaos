#include "TopScoreState.h"
#include <iostream>
#include "Constants.h"

TopScoreState::TopScoreState(GameStateManager& gsm) :gsm(gsm), background("Resources/Backgrounds/leaderBg.jpg", 1)
{
	background.setVector(-1, 0);
}

void TopScoreState::Update(sf::RenderWindow * window, float frametime)
{
	//background.Update();
}

void TopScoreState::Draw(sf::RenderWindow * window)
{
	background.Draw(window);
	window->draw(leaderboardHeader);
	window->draw(pressEnterMessage);
	for (int i = 0; i < Options.size(); i++)
	{
		window->draw(*Options[i]);
	}


	window->draw(scoreMessage);
	window->draw(first);
	window->draw(second);
	window->draw(third);
	window->draw(fourth);
	window->draw(fifth);
}

void TopScoreState::Init()
{
	bgSprite.setTexture(bg);
	bgSprite.setPosition(bgx, bgy);
	bgSprite.setScale(WINWIDTH*WINSCALE / bgSprite.getGlobalBounds().width, WINHEIGHT*WINSCALE / bgSprite.getGlobalBounds().height);
	if (!font.loadFromFile("Resources/GOTHIC.TTF"))
	{
		std::cout << "unable to load from file" << std::endl;
	}

	
	leaderboardHeader.setFont(font);
	leaderboardHeader.setString("LEADERBOARD");
	leaderboardHeader.setCharacterSize(50);
	leaderboardHeader.setPosition(WINWIDTH*WINSCALE / 2 - leaderboardHeader.getGlobalBounds().width / 2, 60);
	leaderboardHeader.setColor(sf::Color(255, 0, 0));

	int offset = 150;
	for (sf::Text *t : Options)
	{
		t->setPosition(170, offset);
		t->setCharacterSize(45);
		t->setColor(sf::Color(255, 0, 0));
		offset += 65;
	}

	scoreMessage.setFont(font);
	scoreMessage.setString("Score");
	scoreMessage.setCharacterSize(45);
	scoreMessage.setPosition(400, 150);
	scoreMessage.setColor(sf::Color(255, 0, 0));

	/* Reading Scores to display in leaderboard */
	readTopScores();

	first.setFont(font);
	first.setString(topScores[0]);
	first.setCharacterSize(45);
	first.setPosition(400, 150 + 65);
	first.setColor(sf::Color(255, 0, 0));

	second.setFont(font);
	second.setString(topScores[1]);
	second.setCharacterSize(45);
	second.setPosition(400, 150 + 65*2);
	second.setColor(sf::Color(255, 0, 0));

	third.setFont(font);
	third.setString(topScores[2]);
	third.setCharacterSize(45);
	third.setPosition(400, 150 + 65 * 3);
	third.setColor(sf::Color(255, 0, 0));

	fourth.setFont(font);
	fourth.setString(topScores[3]);
	fourth.setCharacterSize(45);
	fourth.setPosition(400, 150 + 65 * 4);
	fourth.setColor(sf::Color(255, 0, 0));
	
	fifth.setFont(font);
	fifth.setString(topScores[4]);
	fifth.setCharacterSize(45);
	fifth.setPosition(400, 150 + 65 * 5);
	fifth.setColor(sf::Color(255, 0, 0));

	pressEnterMessage.setFont(font);
	pressEnterMessage.setString("Press 'Enter' to go back");
	pressEnterMessage.setCharacterSize(45);
	pressEnterMessage.setPosition(WINWIDTH*WINSCALE / 2 - pressEnterMessage.getGlobalBounds().width / 2, 590);
	pressEnterMessage.setColor(sf::Color(255, 0, 0));

}

void TopScoreState::KeyPressed(sf::Keyboard::Key key)
{

	if (key == sf::Keyboard::Return)
	{

		gsm.SetState(GameStateManager::MENUSTATE);
		gsm.Init();
	}

}

void TopScoreState::readTopScores()
{
	int x;

	std::ifstream readFile("Resources/gameData/scores.txt");

	while (!readFile.eof())
	{
		readFile >> x;

		fileScores.push_back(x);

	}

	readFile.close();

	fileScores.pop_back();

	std::sort(fileScores.begin(), fileScores.end());

	int j = 0;

	for (int i = fileScores.size() - 1; j < 5; i--)
	{
		topScores[j] = std::to_string(fileScores[i]);
		j++;
	}
}