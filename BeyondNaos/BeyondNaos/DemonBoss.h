#pragma once
#include "Enemy.h"


class DemonBoss : public Enemy {
public:
	DemonBoss(TileMap& tm);
	bool isSpawned();
	void getNextPosition();
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);
	void setSpawn(bool sp);
private:
	bool spawn = false;
	long elapsed;
	std::vector<sf::IntRect*> sprites;
	sf::Sprite *s;
	sf::Texture *t;
	sf::IntRect *rect;
	sf::Clock fireTimer;
	Animation animation;
};

