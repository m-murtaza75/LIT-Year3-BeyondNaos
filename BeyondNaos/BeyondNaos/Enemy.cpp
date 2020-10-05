#include "Enemy.h"



Enemy::Enemy(TileMap &tm): MapObject(tm) {

}

bool Enemy::isFiring()
{
	return firing;
}

bool Enemy::isFireSpawned()
{
	return enemyFireSpawn;
}

bool Enemy::isDead() {
	return dead;
}

int Enemy::getDamage() 
{
	return damage;
}

int Enemy::getPoints()
{
	return points;
}


void Enemy::hit(int damage) {
	if (dead || flinching) return;
	health -= damage;
	if (health < 0) health = 0;
	if (health == 0) dead = true;
	flinching = true;
	flinchTimer.restart();
	
}

void Enemy::setFiring(bool fire)
{
	firing = fire;
}

void Enemy::setFireSpawned(bool sp)
{
	enemyFireSpawn = sp;
}

void Enemy::Update(float frametime) {
}

void Enemy::Draw(sf::RenderWindow * window) 
{

}