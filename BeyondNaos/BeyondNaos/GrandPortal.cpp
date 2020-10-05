#include "GrandPortal.h"

GrandPortal::GrandPortal(TileMap& tm) : MapObject(tm)
{
	width = 30;
	height = 150;
	cWidth = 30;
	cHeight = 150;

	//load sprite
	t = new sf::Texture();
	s = new sf::Sprite();
	rect = new sf::IntRect();
	if (!t->loadFromFile("Resources/Sprites/grandPortal/grandPortalSprite.png"))
	{
		std::cout << "Cannot load grandPortalSprite.png" << std::endl;
	}
	s->setTexture(*t);
	for (int i = 0; i < 4; i++)
	{
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(120);

}

void GrandPortal::Update(float frametime)
{
	animation.Update(frametime);
}

void GrandPortal::Draw(sf::RenderWindow *window)
{
	setMapPosition();

	*rect = animation.getImage();
	s->setTextureRect(*rect);
	s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height);
	s->setScale(1.0, 1.0);
	window->draw(*s);

}