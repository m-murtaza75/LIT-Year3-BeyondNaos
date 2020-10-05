#include "WitchFireBall.h"

WitchFireBall::WitchFireBall(TileMap & tm, bool left) : MapObject(tm)
{
	moveSpeed = -8.3;

	left = true;

	if (left)
	{
		dx = moveSpeed;
	}

	width = 30;
	height = 30;
	cWidth = 30;
	cHeight = 30;

	

	//load sprite
	t = new sf::Texture();
	s = new sf::Sprite();
	rect = new sf::IntRect();
	if (!t->loadFromFile("Resources/Sprites/Enemies/BossEnemies/witchFireBall.png"))
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

void WitchFireBall::setHit()
{
	if (hit) return;
	hit = true;
	animation.setFrames(&hitSprites);
	animation.setDelay(70);
	dx = 0;
}


bool WitchFireBall::shouldRemove()
{
	return remove;
}

void WitchFireBall::Update(float frametime)
{
	checkTileMapCollision();
	setPosition(xTemp, yTemp);
	if (dx == 0 && !hit)
	{
		setHit();
	}
	animation.Update(frametime);
	if (hit && animation.hasPlayedOnce())
	{
		remove = true;
	}
}



void WitchFireBall::Draw(sf::RenderWindow *window)
{
	setMapPosition();

	*rect = animation.getImage();
	s->setTextureRect(*rect);
	s->setPosition((int)x + xMap - width / 2, (int)y + yMap - height);
	s->setScale(1.0, 1.0);
	window->draw(*s);

}