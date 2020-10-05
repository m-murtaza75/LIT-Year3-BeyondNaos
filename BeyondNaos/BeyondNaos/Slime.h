#pragma once
#include "Enemy.h"

class Slime : public Enemy {
public:
	Slime(TileMap& tm);
	void getNextPosition();
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);

private:
	std::vector<sf::IntRect*> sprites;
	sf::Sprite *ss;
	sf::Texture *t;
	sf::IntRect *rect;
	Animation animation;
};


