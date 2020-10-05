#pragma once
#include "MapObject.h"

class Heart : public MapObject
{
public:
	Heart(TileMap& tm);
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);


private:
	sf::Texture *t;
	sf::Sprite *s;
	sf::IntRect *rect;
};