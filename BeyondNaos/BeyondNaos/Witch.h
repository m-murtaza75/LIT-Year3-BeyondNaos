#pragma once
#include "Enemy.h"

class Witch : public Enemy
{
public:
	Witch(TileMap& tm);
	void getNextPosition();
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);


private:
	int flyCounter = 1;
	long elapsed;
	sf::Sprite *s;
	sf::Texture *t;
	sf::IntRect *rect;
	sf::Clock fireTimer;

};