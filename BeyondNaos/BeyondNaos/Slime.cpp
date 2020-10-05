#include "Slime.h"
#include <iostream>
Slime::Slime(TileMap& tm) : Enemy(tm) {
	moveSpeed = 0.2;
	maxSpeed = 0.5;
	fallSpeed = 0.2;
	maxFallSpeed = 10.0;
	width = 30;
	height = 30;
	cWidth = 40;
	cHeight = 40;

	health = maxHealth = 5;
	damage = 3;
	points = 2;

	ss = new sf::Sprite();
	t = new sf::Texture();
	rect = new sf::IntRect();

	if (!t->loadFromFile("Resources/Sprites/Enemies/Slime.png")) { std::cout << "Slime gif not found" << std::endl; }
	ss->setTexture(*t);
	for (int i = 0; i < 3; i++) {
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(300);

	right = true;
	facingRight = true;

}

void Slime::getNextPosition() {
	//movement
	if (left) {
		dx -= moveSpeed;
		if (dx < -moveSpeed) {
			dx = -maxSpeed;
		}
	}
	else if (right) {
		dx += moveSpeed;
		if (dx > maxSpeed) {
			dx = maxSpeed;
		}
	}
	//falling

	if (falling) {
		dy += fallSpeed;
	}
}




void Slime::Update(float frametime) {
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
	if (right && dx == 0) {
		right = false;
		left = true;
		facingRight = false;
	}
	else if (left && dx == false) {
		right = true;
		left = false;
		facingRight = true;
	}
	animation.Update(frametime);
}

void Slime::Draw(sf::RenderWindow * window) {
	//if (notOnScreen()) return;
	setMapPosition();


	if (facingRight) {

		*rect = animation.getImage();
		ss->setTextureRect(*rect);
		ss->setPosition((int)x + xMap - width / 2, (int)y + yMap - height - 5);
		ss->setScale(2, 2);
		window->draw(*ss);
	}
	else {
		*rect = animation.getImage();
		ss->setTextureRect(*rect);
		ss->setPosition((int)(x + xMap - width / 2 + width), (int)(y + yMap - height - 5));
		ss->setScale(-2, 2);
		window->draw(*ss);
	}

}