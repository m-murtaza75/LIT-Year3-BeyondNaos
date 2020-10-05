#pragma once
#include "Enemy.h"


class spider : public Enemy {
public:
	spider(TileMap& tm);
	void getNextPosition();
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);
	~spider();
private:
	std::vector<sf::IntRect*> sprites;
	sf::Sprite *s;
	sf::Texture *t;
	sf::IntRect *rect;
	Animation animation;
};

