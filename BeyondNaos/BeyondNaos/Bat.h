#pragma once
#include "Enemy.h"

class Bat : public Enemy 
{
public:
	Bat(TileMap& tm);
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);
	//void checkAttack(Player* &player);

private:
	long elapsed;
	std::vector<sf::IntRect*> sprites;
	sf::Sprite *s;
	sf::Texture *t;
	sf::IntRect *rect;
	sf::Clock fireTimer;
	Animation animation;
};

