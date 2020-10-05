#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Background.h"


class SelectLevelState : public GameState
{
public:
	class GameStateManager& gsm;
	SelectLevelState(class GameStateManager& gsm);
	void Update(sf::RenderWindow* window, float frametime);
	void Draw(sf::RenderWindow* window);
	void Init();
	void KeyPressed(sf::Keyboard::Key key);
	void selected();


private:
	sf::Texture bg;
	sf::Sprite bgSprite;
	Background background;
	double bgx = 0, bgy = 0;
	int currentChoice = 0;
	sf::Font font;
	sf::Text selectLevelHeader;
	std::vector<sf::Text*> Options = {
		new sf::Text("Level 1",font),
		new sf::Text("Level 2",font),
		new sf::Text("Level 3",font)
	};
	sf::Text pressEscapeMessage;

};