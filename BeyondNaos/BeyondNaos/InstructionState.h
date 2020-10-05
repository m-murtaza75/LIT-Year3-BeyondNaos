#pragma once
#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Background.h"
#include <string>

class InstructionState : public GameState
{
public:
	class GameStateManager& gsm;
	InstructionState(class GameStateManager& gsm);
	void Update(sf::RenderWindow* window, float frametime);
	void Draw(sf::RenderWindow* window);
	void Init();
	void KeyPressed(sf::Keyboard::Key key);

private:

	sf::Texture bg;
	sf::Sprite bgSprite;
	Background background;
	double bgx = 0, bgy = 0;
	sf::Font font;
	sf::Text instructionHeader;
	sf::Text instructionMessage;
	sf::Text pressEnterMessage;





};