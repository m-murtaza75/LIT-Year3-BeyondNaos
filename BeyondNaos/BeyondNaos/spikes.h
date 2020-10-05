#pragma once
#include "Enemy.h"

class spikes : public Enemy {
public:
	spikes(TileMap& tm);
	void getNextPosition();
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);

private:
	long elapsed;
	std::vector<sf::IntRect*> sprites;
	sf::Sprite *spike;
	sf::Texture *t;
	sf::IntRect *rect;
	sf::Clock fireTimer;
	Animation animation;
};

