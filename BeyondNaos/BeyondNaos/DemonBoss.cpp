#include "DemonBoss.h"
#include <iostream>


DemonBoss::DemonBoss(TileMap& tm) : Enemy(tm)
{
	moveSpeed = 4.2;
	maxSpeed = 4.2;
	fallSpeed = 0.0;
	maxFallSpeed = 0.0;
	width = 80;
	height = 80;
	cWidth = 80;
	cHeight = 50;

	health = maxHealth = 45;

	firing = false;

	damage = 15;

	s = new sf::Sprite();
	t = new sf::Texture();
	rect = new sf::IntRect();

	if (!t->loadFromFile("Resources/Sprites/Enemies/BossEnemies/demonAnimation.png"))
	{
		std::cout << "Demon-Idle.png not found" << std::endl;
	}

	s->setTexture(*t);
	for (int i = 0; i < 6; i++)
	{
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(300);

	
	left = true;


	facingLeft = true;

}

bool DemonBoss::isSpawned()
{
	return spawn;
}

void DemonBoss::getNextPosition()
{
	//movement
	if (left)
	{
		dx -= moveSpeed;
		if (dx < -moveSpeed)
		{
			dx = -maxSpeed;
		}
	}
	else if (right)
	{
		dx += moveSpeed;
		if (dx > maxSpeed)
		{
			dx = maxSpeed;
		}
	}
	//falling

	if (falling)
	{
		//dy += fallSpeed;
	}
}




void DemonBoss::Update(float frametime)
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

	if (elapsed > 600)
	{
		firing = true;

		fireTimer.restart();

	}

	//if it hits a wall, go other direction
	if (right && dx == 0)
	{
		right = false;
		left = true;
		facingRight = false;
	}
	else if (left && dx == false)
	{
		right = true;
		left = false;
		facingRight = true;
	}
	animation.Update(frametime);
}

void DemonBoss::Draw(sf::RenderWindow * window)
{
	//if (notOnScreen()) return;
	setMapPosition();


	if (facingRight)
	{

		*rect = animation.getImage();
		s->setTextureRect(*rect);
		s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height - 5);
		s->setScale(2, 2);
		window->draw(*s);
	}
	else
	{
		*rect = animation.getImage();
		s->setTextureRect(*rect);
		s->setPosition((int)(x + xMap - width / 2 + width), (int)(y + yMap - height - 5));
		s->setScale(-2, 2);
		window->draw(*s);
	}

}
void DemonBoss::setSpawn(bool sp)
{
	spawn = sp;
}

