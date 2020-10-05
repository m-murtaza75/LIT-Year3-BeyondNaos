#include "Witch.h"
#include <iostream>

Witch::Witch(TileMap& tm) : Enemy(tm) 
{
	width = 60;
	height = 62;
	cWidth = 60;
	cHeight = 62;

	left = true;

	firing = false;

	health = maxHealth = 60;
	damage = 30;

	s = new sf::Sprite();
	t = new sf::Texture();
	rect = new sf::IntRect();

	if (!t->loadFromFile("Resources/Sprites/Enemies/witchL.png")) 
	{ 
		std::cout << "witchL.png not found" << std::endl; 
	}
	s->setTexture(*t);

	facingLeft = true;

}



void Witch::getNextPosition()
{
	//movement
	if (flyCounter <= 90)
	{
		y = (double)getY() - 3;


		flyCounter++;
	}

	if (flyCounter > 90)
	{
		y = (double)getY() + 3;
		flyCounter++;
	}

	if (flyCounter > 180)
	{
		flyCounter = 1;
	}

}



void Witch::Update(float frametime)
{
	getNextPosition();
	checkTileMapCollision();
	setPosition(xTemp, yTemp);

	//check flinching
	if (flinching) 
	{
		long elapsed = flinchTimer.getElapsedTime().asMilliseconds();
		if (elapsed > 400) 
		{
			flinching = false;
		}
	}

	elapsed = fireTimer.getElapsedTime().asMilliseconds();

	if (elapsed > 300)
	{
		firing = true;

		fireTimer.restart();

	}
}

void Witch::Draw(sf::RenderWindow * window)
{
	setMapPosition();

	s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height - 5);
	s->setScale(2, 2);
	window->draw(*s);

}