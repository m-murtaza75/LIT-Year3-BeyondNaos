#pragma once
#include "MapObject.h"
#include "FireBall.h"
#include "Enemy.h"
#include "Witch.h"
class Player: public MapObject 
{
public:
	Player(TileMap& tm);
	bool isDead();
	void setDead(bool b);
	int getHealth();
	int getMaxHealth();
	int getFire();
	int getMaxFire();
	int getScore();
	void updateScore(int s);
	void setFiring();
	void increaseFire(int f);
	void increaseHealth(int hValue);
	void decreaseHealth(int hValue);
	void setScratching();
	void setGliding(bool b);
	void checkAttack(std::vector<Enemy*>&enemies);
	void checkAttackOnWitch(Witch* &witch);
	void getNextPosition();
	void hit(int damage);
	void Update(float frametime);
	void Draw(sf::RenderWindow *window);

private:
	//player declarations
	int health = 0, maxHealth = 100, fire = 0, maxFire = 0, score = 0;
	bool dead = false, flinching = false;
	long flinchtimer = 0;
	//fireball
	bool firing = false;
	int fireCost = 0;
	int fireBallDamage = 0;
	long fr = 0;
	std::vector<FireBall*> fireballs;

	//scratch
	bool scratching = false;
	int scratchDamage = 0;
	int scratchRange = 0;

	//gliding
	bool gliding = false;

	sf::Texture *t;
	sf::Sprite *s;
	sf::Clock clock;

	FireBall *fb;

	//animations
	std::vector<sf::IntRect*> *bi;
	std::vector<std::vector<sf::IntRect*>*> sprites;
	sf::IntRect *rect;
	const int numFrames[7] = { 2,8,1,2,4,2,5 };

	//animation actions
	static const int IDLE = 0;
	static const int WALKING = 1;
	static const int JUMPING = 2;
	static const int FALLING = 3;
	static const int GLIDING = 4;
	static const int FIREBALL = 5;
	static const int SCRATCHING = 6;

};

