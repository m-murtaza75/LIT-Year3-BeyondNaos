#include "Boss1.h"
#include <iostream>


Boss1::Boss1(TileMap& tm) : Enemy(tm)
{
	moveSpeed = 0.8;
	maxSpeed = 1.5;
	fallSpeed = 0.2;

	maxFallSpeed = 8.0;
	jumpStart = -7.0;
	stopJumpSpeed = 0.4;

	width = 60;
	height = 60;
	cWidth = 60;
	cHeight = 60;

	health = maxHealth = 30;
	damage = 10;

	s = new sf::Sprite();
	t = new sf::Texture();
	rect = new sf::IntRect();

	if (!t->loadFromFile("Resources/Sprites/Enemies/BossEnemies/forestGuardian.png"))
	{
		std::cout << "forestGuardian.png not found" << std::endl;
	}

	s->setTexture(*t);
	


	right = true;
	facingRight = true;

}

bool Boss1::isSpawned()
{
	return spawn;
}

void Boss1::getNextPosition()
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
	
	// Condition to initiate jump
	jumpTimer = clock.getElapsedTime().asMilliseconds();
	if (jumpTimer > 1800)
	{
		jumping = true;

	}
	

	//jumping

	if (jumping && !falling) 
	{
		dy = jumpStart;
		falling = true;

		jumping = false;

		clock.restart();
	}

	
	//falling

	if (falling)
	{
		dy += fallSpeed;
	}

}




void Boss1::Update(float frametime)
{
	getNextPosition();
	checkTileMapCollision();
	setPosition(xTemp, yTemp);

	//check flinching
	if (flinching)
	{
		long elapsed = flinchTimer.getElapsedTime().asMilliseconds();
		if (elapsed > 600)
		{
			flinching = false;
		}
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
	//animation.Update(frametime);
}

void Boss1::Draw(sf::RenderWindow * window)
{
	//if (notOnScreen()) return;
	setMapPosition();


	if (facingRight)
	{
		s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height - 5);
		s->setScale(2, 2);
		window->draw(*s);
	}
	else
	{
		s->setPosition((int)(x + xMap - width / 2 + width), (int)(y + yMap - height - 5));
		s->setScale(-2, 2);
		window->draw(*s);
	}

}

void Boss1::setSpawn(bool sp)
{
	spawn = sp;
}