#include "bouncer.h"
#include <iostream>
bouncer::bouncer(TileMap& tm): Enemy(tm) {
	moveSpeed = 0.2;
	maxSpeed = 0.5;
	fallSpeed = 0.2;
	maxFallSpeed = 10.0;
	width = 30;
	height = 30;
	cWidth = 40;
	cHeight = 40;
	jumpStart = -7.9;
	stopJumpSpeed = 0.3;
	
	


	health = maxHealth = 9;
	damage = 4;
	points = 3;

	sss = new sf::Sprite();
	t = new sf::Texture();
	rect = new sf::IntRect();

	if (!t->loadFromFile("Resources/Sprites/Enemies/bouncer1.png")) { std::cout << "bouncer gif not found" << std::endl; }
	sss->setTexture(*t);
	for (int i = 0; i < 3; i++) {
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(300);
	//facingRight = true;

}


	


void bouncer::getNextPosition() {
	//movement
	
	
	JumpTimer = clock.getElapsedTime().asMilliseconds();

		if (JumpTimer > 1500) {
			jumping = true;
		}


		if (jumping && !falling) {
			dy = jumpStart;
			falling = true;
			jumping = false;
			clock.restart();
			

		}
		//falling
		if (falling) {
			dy += fallSpeed;

		}
	}



void bouncer::Update(float frametime) {
	getNextPosition();
	checkTileMapCollision();
	setPosition(xTemp, yTemp);

	//check flinching
	if (flinching) {
		long elapsed = flinchTimer.getElapsedTime().asMilliseconds();
		if (elapsed > 400) {
			flinching = false;
		}
	}
	//if it hits a wall, go other direction
	if (down && dy == 0) {
		down = false;
		up = true;
	}
	else if (up && dy == false) {
		down = true;
		up = false;
	}
	animation.Update(frametime);
}

void bouncer::Draw(sf::RenderWindow * window) {
	//if (notOnScreen()) return;
	setMapPosition();


	if (facingLeft) {

		*rect = animation.getImage();
		sss->setTextureRect(*rect);
		sss->setPosition((int)x + xMap - width / 2, (int)y + yMap - height - 5);
		sss->setScale(2, 2);
		window->draw(*sss);
	}
	else {
		*rect = animation.getImage();
		sss->setTextureRect(*rect);
		sss->setPosition((int)(x + xMap - width / 2 + width), (int)(y + yMap - height - 5));
		sss->setScale(-2, 2);
		window->draw(*sss);
	}

}