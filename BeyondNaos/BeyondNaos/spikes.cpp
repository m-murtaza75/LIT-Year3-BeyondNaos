#include "spikes.h"
#include <iostream>


spikes::spikes(TileMap& tm) : Enemy(tm)
{
	width = 30;
	height = 30;
	cWidth = 40;
	cHeight = 40;

	down = true;

	health = maxHealth = 2;
	damage = 1;

	spike = new sf::Sprite();
	t = new sf::Texture();
	rect = new sf::IntRect();

	if (!t->loadFromFile("Resources/Sprites/Enemies/spikes.png")) { std::cout << "spikes.png not found" << std::endl; }
	spike->setTexture(*t);
	for (int i = 0; i < 3; i++)
	{
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(100);
}

void spikes::getNextPosition()
{
}

void spikes::Update(float frametime)
{
	checkTileMapCollision();
	setPosition(xTemp, yTemp);

	elapsed = fireTimer.getElapsedTime().asMilliseconds();

	if (elapsed > 1400)
	{
		fireTimer.restart();

	}


	animation.Update(frametime);
}

void spikes::Draw(sf::RenderWindow * window)
{
	setMapPosition();

	
	*rect = animation.getImage();
	spike->setTextureRect(*rect);
	spike->setPosition((int)x + xMap - width / 2, (int)y + yMap - height - 5);
	spike->setScale(2, 2);
	window->draw(*spike);

}