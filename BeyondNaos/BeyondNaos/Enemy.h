#pragma once
#include "MapObject.h"
class Enemy: public MapObject {
public:
	Enemy(TileMap &tm);
	bool isFiring();
	bool isFireSpawned();
	bool isDead();
	int getDamage();
	int getPoints();
	void hit(int damage);
	void setFiring(bool fire);
	void setFireSpawned(bool sp);
	void setDead(bool d);
	virtual void Update(float frametime);
	virtual void Draw(sf::RenderWindow *window);

protected:
	int health = 0, maxHealth = 0, damage = 0, points = 1;
	bool dead = false, flinching = false, firing = false, enemyFireSpawn = false;
	sf::Clock flinchTimer;
};
