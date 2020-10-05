#pragma once
#include "Enemy.h"

class bouncer : public Enemy {
public:
	bouncer(TileMap& tm);
	void getNextPosition();
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);

private:
	long JumpTimer;
	std::vector<sf::IntRect*> sprites;
	sf::Sprite *sss;
	sf::Texture *t;
	sf::IntRect *rect;
	sf::Clock clock;
	Animation animation;
};


