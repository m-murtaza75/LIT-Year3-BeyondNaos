#pragma once
#include "MapObject.h"

class Portal : public MapObject
{
public:
	Portal(TileMap& tm);
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);


private:
	std::vector<sf::IntRect*> sprites;
	sf::Texture *t;
	sf::Sprite *s;
	sf::IntRect *rect;
};