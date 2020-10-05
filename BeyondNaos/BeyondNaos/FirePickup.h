#pragma once
#include "MapObject.h"

class FirePickup : public MapObject
{
public:
	FirePickup(TileMap& tm);
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);


private:
	sf::Texture *t;
	sf::Sprite *s;
	sf::IntRect *rect;
};