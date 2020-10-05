#pragma once
#include "Enemy.h"


class Boss1 : public Enemy 
{
public:
	Boss1(TileMap& tm);
	bool isSpawned();
	void getNextPosition();
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);
	void setSpawn(bool sp);


private:
	long jumpTimer;
	bool spawn = false;
	sf::Sprite *s;
	sf::Texture *t;
	sf::IntRect *rect;
	sf::Clock clock;
};

