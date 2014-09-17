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

Projectile::Projectile(EnemyManager * _enemyList, Player * _player1)
{
	player1 = _player1;
	playerOrEnemy = 0;
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
		if (direction % 2 != 0)
			x += 16*direction;
		else {
			y += 16 * (direction / abs(direction));
		}
	}
	mySprite.setPosition(x, y);
	if (playerOrEnemy == 0) {
		for (int i = 0; i < 32; i++) {
			if (!enemyList->getEnemy(i)->isActivated())
				break;
			if (IS_BETWEEN(x, enemyList->getEnemy(i)->get_x()-13, enemyList->getEnemy(i)->get_x()+13) && IS_BETWEEN(y, enemyList->getEnemy(i)->get_y()-16, enemyList->getEnemy(i)->get_y()+16)) {
				enemyList->getEnemy(i)->hit(2);
				inUse = false;
				break;
			}
		}
		if (lifeClock.getElapsedTime().asSeconds() > 1.5)
			inUse = false;
	} else if (playerOrEnemy == 1) {
		if (player1 != NULL) {
			if (IS_BETWEEN(x, player1->get_x()-13, player1->get_x()+13) && IS_BETWEEN(y, player1->get_y()-16, player1->get_y()+16)) {
				player1->hit(1);
				inUse = false;
			}
			if (lifeClock.getElapsedTime().asSeconds() > 1.5)
				inUse = false;
		}
	}
}

void Projectile::setDirection(int dir)
{
	direction = dir;
}

void Projectile::activate(float _x, float _y, int _direction, int _playerOrEnemy)
{
	playerOrEnemy = _playerOrEnemy;
	x = _x;
	y = _y;
	direction = _direction;
	inUse = true;
	loadImage.loadFromFile("images/entities/bullet.png");
	myTexture.loadFromImage(loadImage);
	mySprite.setTexture(myTexture);
	mySprite.setColor(sf::Color::Yellow);
	
	if (direction % 2 != 0) {
		mySprite.setRotation(0);
		y = y + (rand() % 5 - 3);
		x += (direction * 16);
	}
	else {
		mySprite.setRotation(90);
		x = x + (rand() % 5 - 3);
		y += (direction * 8);
	}
	if (direction > 0) {
		mySprite.setScale(1, 1);
	}
	if (direction < 0 && !reversed) {
		mySprite.setScale(-1, 1);
	}
	if (playerOrEnemy == 0) {
		mySprite.setColor(sf::Color::White);
	} else if (playerOrEnemy == 1) {
		mySprite.setColor(sf::Color::Green);
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
