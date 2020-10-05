#include "Heart.h"

Heart::Heart(TileMap& tm) : MapObject(tm)
{
	width = 30;
	height = 30;
	cWidth = 30;
	cHeight = 30;

	//load sprite
	t = new sf::Texture();
	s = new sf::Sprite();
	rect = new sf::IntRect();
	if (!t->loadFromFile("Resources/Sprites/Health/heart2.png"))
	{
		std::cout << "Cannot load image heart2.png" << std::endl;
	}

	s->setTexture(*t);
	
}

void Heart::Update(float frametime)
{
	
}

void Heart::Draw(sf::RenderWindow *window)
{
	setMapPosition();

	s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height);
	s->setScale(1.0, 1.0);
	window->draw(*s);

}