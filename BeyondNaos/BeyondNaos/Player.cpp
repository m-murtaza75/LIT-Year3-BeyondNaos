#include "Player.h"
#include <iostream>

Player::Player(TileMap& tm): MapObject(tm) 
{
	width = 30;
	height = 30;
	cWidth = 30;
	cHeight = 30;

	moveSpeed = 0.3;
	maxSpeed = 1.6;
	stopSpeed = 0.4;
	fallSpeed = 0.15;
	maxFallSpeed = 8.0;
	jumpStart = -6.9;
	stopJumpSpeed = 0.3;

	facingRight= true;

	health  = 100;

	fire = maxFire = 30;

	fireCost = 1;
	fireBallDamage = 5;

	scratchDamage = 8;
	scratchRange = 40;

	t = new sf::Texture();
	s = new sf::Sprite();
	if(!t->loadFromFile("Resources/Sprites/Player/playersprites.png")) std::cout << "Player Sprite not found."<<std::endl;
	s->setTexture(*t);
	for (int i = 0; i < 7; i++) 
	{
		bi = new std::vector<sf::IntRect*>;
		for (int j = 0; j < numFrames[i]; j++) 
		{
			if (i != 6) 
			{
				 bi->push_back(new sf::IntRect(j*width, i*height, width, height));
			}
			else 
			{
				bi->push_back(new sf::IntRect(j*width*2, i*height, width*2, height));
			}
		}
		sprites.push_back(&*bi);
		bi = NULL;
	}

	currentAction = IDLE;
	animation.setFrames(&*sprites.at(IDLE));
	animation.setDelay(400);
	rect = new sf::IntRect();


}

bool Player::isDead()
{
	return dead;
}

void Player::setDead(bool b)
{
	dead = b;
}


int Player::getHealth() 
{
	return health; 
}

int Player::getMaxHealth() 
{ 
	return maxHealth; 
}

int Player::getFire() 
{ 
	return fire; 
}
int Player::getMaxFire() 
{ 
	return maxFire; 
}

int Player::getScore()
{
	return score;
}

void Player::updateScore(int s)
{
	score = s;
}

void Player::setFiring() 
{ 
	firing = true; 
}

void Player::increaseHealth(int hValue)
{
	health += hValue;

	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

void Player::increaseFire(int f)
{
	fire += f;

	if (fire > maxFire)
	{
		fire = maxFire;
	}
}

void Player::decreaseHealth(int hValue)
{
	health -= hValue;

	if (health < 0)
	{
		health = 0;
	}
}


void Player::setScratching() 
{ 
	scratching = true; 
}

void Player::setGliding(bool b) 
{ 
	gliding = b; 
}


void Player::checkAttack(std::vector<Enemy*>& enemies) 
{
	for (int i = 0; i < enemies.size(); i++) {
		Enemy *e = enemies[i];
		if (scratching) {
			if (facingRight) {
				if (e->getX() > x && e->getX() < x + scratchRange && e->getY() > y - height / 2 && e->getY() < y + height / 2) {
					e->hit(scratchDamage);
					score += e->getPoints();
				}
			}
			else {
				if (e->getX() < x && e->getX()>x-scratchRange&&e->getY()>y-height/2 && e->getY()<y+height/2 ){
					e->hit(scratchDamage);
					score += e->getPoints();
				}
			}
		}
		for (int j = 0; j < fireballs.size(); j++) {
			if (fireballs[j]->intersects(*e)) 
			{
				e->hit(fireBallDamage);
				fireballs[j]->setHit();
				score += e->getPoints();
				break;
			}
		}
		if (intersects(*e)) {
			hit(e->getDamage());
		}
	}
}

void Player::checkAttackOnWitch(Witch* &witch)
{
	Witch *w = witch;


	if (scratching) 
	{
		if (facingRight) 
		{
			if (w->getX() > x && w->getX() < x + scratchRange && w->getY() > y - height / 2 && w->getY() < y + height / 2) 
			{
				w->hit(scratchDamage);
				score += w->getPoints();
			}
		}
		else 
		{
			if (w->getX() < x && w->getX() > x - scratchRange && w->getY() > y - height / 2 && w->getY() < y + height / 2)
			{
				w->hit(scratchDamage);
				score += w->getPoints();
			}
		}
	}
	for (int j = 0; j < fireballs.size(); j++) 
	{
		if (fireballs[j]->intersects(*w))
		{
			w->hit(fireBallDamage);
			fireballs[j]->setHit();
			score += w->getPoints();
			break;
		}
	}
	if (intersects(*w))
	{
		hit(w->getDamage());
	}

}


void Player::hit(int damage) 
{

	if (flinching) return;
	health -= damage;
	if (health < 0) health = 0;
	if (health == 0) dead = true;
	flinching = true;
	clock.restart();
}

void Player::getNextPosition() {
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
	else {
		if (dx > 0) {
			dx -= stopSpeed;
			if (dx < 0) {
				dx = 0;
			}
		}
		else if (dx < 0) {
			dx += stopSpeed;
			if (dx > 0) {
				dx = 0;
			}
		}
	}

	//cannot move while moving

	if ((currentAction == SCRATCHING || currentAction == FIREBALL) && !(jumping || falling)) {
		dx = 0;
	}

	//jumping

	if (jumping && !falling) {
		dy = jumpStart;
		falling = true;
	}

	//falling

	if (falling) {
		if (dy > 0 && gliding) dy += fallSpeed *0.01;
		else dy += fallSpeed;

		if (dy > 0) jumping = false;
		if (dy < 0 && !jumping) dy += stopJumpSpeed;
		if (dy > maxFallSpeed) dy = maxFallSpeed;
	}

}



void Player::Update(float frametime) {
	this->fr = frametime;
	//update position
	getNextPosition();
	checkTileMapCollision();
	setPosition(xTemp, yTemp);

	//check animation for attack has stopped

	if (currentAction == SCRATCHING) {
		if (animation.hasPlayedOnce()) scratching = false;
	}
	if (currentAction == FIREBALL) {
		if (animation.hasPlayedOnce()) firing = false;
	}
	//fireball attack

	//fire += 1;
	if (fire > maxFire) fire = maxFire;
	if (firing && currentAction != FIREBALL) 
	{
		if (fire >= fireCost) 
		{
			fire -= fireCost;
			fb = new FireBall(tileMap, facingRight);
			fb->setPosition(x, y);
			fireballs.push_back(fb);
		}
	}
	//update fireballs
	for (int i = 0; i < fireballs.size(); i++) {
		fireballs[i]->Update(frametime);
		if (fireballs[i]->shouldRemove()) {
			fireballs.erase(fireballs.begin() + i);
			i--;
		}
	}

	if (flinching) {
		long elapsed = clock.getElapsedTime().asMilliseconds();
		if (elapsed > 1000) {
			flinching = false;
		}
	}

	//set animation
	if(scratching){
		if (currentAction != SCRATCHING) {
			currentAction = SCRATCHING;
			animation.setFrames(&*sprites.at(SCRATCHING));
			animation.setDelay(50);
			width = 120;
		}
	}
	else if (firing) {
		if (currentAction != FIREBALL) {
			currentAction = FIREBALL;
			animation.setFrames(&*sprites.at(FIREBALL));
			animation.setDelay(100);
			width = 60;
			height = 90;
		}
	}
	else if (dy > 0) {
		if (gliding) {
			if (currentAction != GLIDING) {
				currentAction = GLIDING;
				animation.setFrames(&*sprites.at(GLIDING));
				animation.setDelay(100);
				width = 60;
                height = 90;
			}
		}
		else if (currentAction != FALLING) {
			currentAction = FALLING;
			animation.setFrames(&*sprites.at(FALLING));
			animation.setDelay(100);
			width = 60;
			height = 90;
		}
	}
	else if (dy < 0) {
		if (currentAction != JUMPING) {
			currentAction = JUMPING;
			animation.setFrames(&*sprites.at(JUMPING));
			animation.setDelay(-1);
			width = 60;
			height = 90;
		}
	}
	else if (left || right) {
		if (currentAction != WALKING) {
			currentAction = WALKING;
			animation.setFrames(&*sprites.at(WALKING));
			animation.setDelay(40);
			width = 60;
			height = 90;
		}
	}
	else {
		if (currentAction != IDLE) {
			currentAction = IDLE;
			animation.setFrames(&*sprites.at(IDLE));
			animation.setDelay(400);
			width = 60;
			height = 90;
		}
	}

	animation.Update(frametime);

	//set direction

	if (currentAction != SCRATCHING && currentAction != FIREBALL) 
	{
		if (right) facingRight = true;
		if (left) facingRight = false;
	}
}

void Player::Draw(sf::RenderWindow * window) 
{
	setMapPosition();

	//draw fireballs

	for (int i = 0; i < fireballs.size(); i++) 
	{
		fireballs[i]->Draw(window);
	}

	//draw player
	if (flinching) 
	{
		long elapsed = clock.getElapsedTime().asMilliseconds();
		if (elapsed / 100 % 2 == 0) 
		{
			return;
		}
	}

	if (facingRight) 
	{

		*rect = animation.getImage();
		s->setTextureRect(*rect);
		s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height / 2);
		s->setScale(1.0f*2, 1.0*2);
		window->draw(*s);
	}
	else 
	{
		*rect = animation.getImage();
		s->setTextureRect(*rect);
		s->setPosition((int)(x + xMap - width / 2 + width), (int)(y + yMap - height / 2));
		s->setScale(-1.0f*2, 1.0*2);
		window->draw(*s);
	}

	/* Condition to check if player falls out of level */
	if (getY() > 1490)
	{
		gliding = false;

		setPosition(60, 350);
		health = health - 20;
		if (currentAction != FALLING)
		{
			currentAction = FALLING;
		}
		
	}


}