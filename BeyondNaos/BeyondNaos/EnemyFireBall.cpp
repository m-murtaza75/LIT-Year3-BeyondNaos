#include "EnemyFireBall.h"


EnemyFireBall::EnemyFireBall(TileMap & tm, bool down) : MapObject(tm)
{
	moveSpeed = 1.3;
	if (down)
	{
		dy = moveSpeed;
	}

	width = 30;
	height = 30;
	cWidth = 14;
	cHeight = 14;

	down = true;

	//load sprite
	t = new sf::Texture();
	s = new sf::Sprite();
	rect = new sf::IntRect();
	if (!t->loadFromFile("Resources/Sprites/Enemies/batFireball.png")) 
	{ 
		std::cout << "Cannot load batFireball sprites" << std::endl; 
	}
	s->setTexture(*t);
	for (int i = 0; i < 4; i++) 
	{
		sprites.push_back(new sf::IntRect(i*width, 0, width, height));
	}

	for (int i = 0; i < 3; i++) 
	{
		hitSprites.push_back(new sf::IntRect(i*width, height, width, height));
	}

	animation.setFrames(&sprites);
	animation.setDelay(70);
}

void EnemyFireBall::setHit()
{
	if (hit) return;
	hit = true;
	animation.setFrames(&hitSprites);
	animation.setDelay(70);
	dy = 0;
}


bool EnemyFireBall::shouldRemove()
{
	return remove;
}

void EnemyFireBall::Update(float frametime)
{
	checkTileMapCollision();
	setPosition(xTemp, yTemp);
	if (dy == 0 && !hit)
	{
		setHit();
	}
	animation.Update(frametime);
	if (hit && animation.hasPlayedOnce())
	{
		remove = true;
	}
}



void EnemyFireBall::Draw(sf::RenderWindow *window)
{
	setMapPosition();

	*rect = animation.getImage();
	s->setTextureRect(*rect);
	s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height);
	s->setScale(1.0, 1.0);
	window->draw(*s);

}