#include "Projectile.h"


Projectile::Projectile(void)
{
	lifeClock.restart();
	loadImage.loadFromFile("images/entities/bullet.png");
	myTexture.loadFromImage(loadImage);
	mySprite.setTexture(myTexture);
	mySprite.setColor(sf::Color::Yellow);
	mySprite.setOrigin(16,8);
	x = 0;
	y = 0;
	inUse = false;
	reversed = false;
}


void Projectile::update(ActionList _actionList)
{
	if (!inUse) {
		x = -1000;
		y = -1000;
	} else {
		x += 16*direction;
	}
	mySprite.setPosition(x, y);
	if (lifeClock.getElapsedTime().asSeconds() > 5)
		inUse = false;
}

void Projectile::setDirection(int dir)
{
	direction = dir;
}

void Projectile::activate(float _x, float _y, int _direction)
{
	x = _x;
	y = _y;
	direction = _direction;
	inUse = true;
	loadImage.loadFromFile("images/entities/bullet.png");
	myTexture.loadFromImage(loadImage);
	mySprite.setTexture(myTexture);
	mySprite.setColor(sf::Color::Yellow);
	if (direction == 1) {
		mySprite.setScale(1, 1);
	}
	if (direction == -1 && !reversed) {
		mySprite.setScale(-1, 1);
	}
	lifeClock.restart();
}

sf::Sprite Projectile::getSprite()
{
	return mySprite;
}

bool Projectile::getInUse()
{
	return inUse;
}

Projectile::~Projectile(void)
{
}
