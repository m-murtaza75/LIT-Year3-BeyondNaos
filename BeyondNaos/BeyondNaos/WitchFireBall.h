#pragma once
#include "MapObject.h"
class WitchFireBall : public MapObject
{
public:
	WitchFireBall(TileMap& tm, bool left);

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