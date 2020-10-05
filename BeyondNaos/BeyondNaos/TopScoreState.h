#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Background.h"
#include <string>

class TopScoreState : public GameState 
{
public:
	class GameStateManager& gsm;
	TopScoreState(class GameStateManager& gsm);
	void Update(sf::RenderWindow* window, float frametime);
	void Draw(sf::RenderWindow* window);
	void Init();
	void KeyPressed(sf::Keyboard::Key key);
	void readTopScores();

private:
	int score;
	
	std::string topScores[5];
	sf::Texture bg;
	sf::Sprite bgSprite;
	Background background;
	double bgx = 0, bgy = 0;
	sf::Font font;
	sf::Text leaderboardHeader;
	sf::Text pressEnterMessage;

	sf::Text scoreMessage;
	sf::Text first;
	sf::Text second;
	sf::Text third;
	sf::Text fourth;
	sf::Text fifth;

	std::vector<int> fileScores;
	std::vector<sf::Text*> Options = 
	{
		new sf::Text("Rank",font),
		new sf::Text("1.",font),
		new sf::Text("2.",font),
		new sf::Text("3.",font),
		new sf::Text("4.",font),
		new sf::Text("5.",font)
	};

};