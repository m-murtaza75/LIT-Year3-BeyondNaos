#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
class GameState 
{
public:
	GameState() {}
	virtual void Update(sf::RenderWindow* window, float frametime) {}
	virtual void Draw(sf::RenderWindow* window) {}
	virtual void Init() {}
	virtual void KeyPressed(sf::Keyboard::Key key) {}
	virtual void KeyReleased(sf::Keyboard::Key key) {}
	virtual void ButtonPressed() {}
	virtual void ButtonReleased() {}

};

