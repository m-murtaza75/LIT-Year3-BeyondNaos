#include "Portal.h"

Portal::Portal(TileMap& tm) : MapObject(tm)
{
	width = 30;
	height = 30;
	cWidth = 30;
	cHeight = 30;

	//load sprite
	t = new sf::Texture();
	s = new sf::Sprite();
	rect = new sf::IntRect();
	if (!t->loadFromFile("Resources/Sprites/portal/portals.png"))
	{
		std::cout << "Cannot load portals.png" << std::endl;
	}
	s->setTexture(*t);
	for (int i = 0; i < 3; i++)
	{
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(250);

}

void Portal::Update(float frametime)
{
	animation.Update(frametime);
}

void Portal::Draw(sf::RenderWindow *window)
{
	setMapPosition();

	*rect = animation.getImage();
	s->setTextureRect(*rect);
	s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height);
	s->setScale(1.0, 1.0);
	window->draw(*s);

}