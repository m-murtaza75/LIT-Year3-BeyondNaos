#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "MenuState.h"
#include "Level1State.h"
#include "Level2State.h"
#include "Level3State.h"
#include "GameCompletionState.h"
#include "GameOverState.h"
#include "TopScoreState.h"
#include "InstructionState.h"
#include "SelectLevelState.h"


class GameStateManager 
{
public:
	static const int MENUSTATE = 0;
	static const int LEVEL1STATE = 1;
	static const int LEVEL2STATE = 2;
	static const int LEVEL3STATE = 3;
	static const int TOPSCORE = 4;
	static const int GAMEOVER = 5;
	static const int INSTRUCTIONSTATE = 6;
	static const int GAMECOMPLETION = 7;
	static const int SELECTLEVEL = 8;

	/* Credit, Highscore, Instructions */

	GameStateManager();
	
	void SetState(int state);
	void Update(sf::RenderWindow* window, float frametime);
	void Draw(sf::RenderWindow* window);
	void Init();
	void KeyPressed(sf::Keyboard::Key key);
	void KeyReleased(sf::Keyboard::Key key);
	void ButtonPressed();
	void ButtonReleased();
	
private:
	std::vector<GameState*> States;
	int currentState;
};