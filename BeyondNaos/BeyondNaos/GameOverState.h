#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Background.h"


class GameOverState : public GameState 
{
public:
	class GameStateManager& gsm;
	GameOverState(class GameStateManager& gsm);
	void Update(sf::RenderWindow* window, float frametime);
	void Draw(sf::RenderWindow* window);
	void Init();
	void KeyPressed(sf::Keyboard::Key key);
	std::string getLastScore();

private:
	std::string playerScore;
	sf::Texture bg;
	sf::Sprite bgSprite;
	Background background;
	double bgx = 0, bgy = 0;
	sf::Font font;
	sf::Text GameOverHeader;
	sf::Text pressEnterMessage;
	sf::Text pressEscapeMessage;
	sf::Text playerScoreMessage;
	
};

