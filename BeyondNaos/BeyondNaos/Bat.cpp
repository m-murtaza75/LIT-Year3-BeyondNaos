#include "Bat.h"
#include <iostream>


Bat::Bat(TileMap& tm) : Enemy(tm)
{
	width = 30;
	height = 30;
	cWidth = 40;
	cHeight = 40;

	down = true;

	firing = false;

	health = maxHealth = 5;
	damage = 8;
	points = 5;

	s = new sf::Sprite();
	t = new sf::Texture();
	rect = new sf::IntRect();

	if (!t->loadFromFile("Resources/Sprites/Enemies/batSprite.png")) { std::cout << "Bat.png not found" << std::endl; }
	s->setTexture(*t);
	for (int i = 0; i < 3; i++) 
	{
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(100);
}

void Bat::Update(float frametime)
{
	checkTileMapCollision();
	setPosition(xTemp, yTemp);

	elapsed = fireTimer.getElapsedTime().asMilliseconds();

	if (elapsed > 900)
	{
		firing = true;
		
		fireTimer.restart();
		
	}

	animation.Update(frametime);
}

void Bat::Draw(sf::RenderWindow * window)
{
	setMapPosition();

	*rect = animation.getImage();
	s->setTextureRect(*rect);
	s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height - 5);
	s->setScale(2, 2);
	window->draw(*s);
	
}