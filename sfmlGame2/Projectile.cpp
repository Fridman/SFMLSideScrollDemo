#include "Projectile.h"
#include "GameScreen.h"

Projectile::Projectile()
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

Projectile::Projectile(EnemyManager * _enemyList)
{
	enemyList = _enemyList;
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
	for (int i = 0; i < 32; i++) {
		if (IS_BETWEEN(x, enemyList->getEnemy(i)->get_x()-13, enemyList->getEnemy(i)->get_x()+13) && IS_BETWEEN(y, enemyList->getEnemy(i)->get_y()-16, enemyList->getEnemy(i)->get_y()+16)) {
			enemyList->getEnemy(i)->hit(1);
			inUse = false;
		}
	}
	if (lifeClock.getElapsedTime().asSeconds() > 3)
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
