#pragma once
#include "MapObject.h"
class EnemyFireBall : public MapObject 
{
public:
	EnemyFireBall(TileMap& tm, bool down);

	void setHit();


	bool shouldRemove();

	void Update(float frametime);
	void Draw(sf::RenderWindow * window);

private:
	bool hit = false;
	bool remove = false;
	std::vector<sf::IntRect*> sprites;
	std::vector<sf::IntRect*> hitSprites;
	sf::Texture *t;
	sf::Sprite *s;
	sf::IntRect *rect;
};

