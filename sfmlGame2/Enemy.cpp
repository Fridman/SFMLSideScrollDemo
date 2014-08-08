#include "Enemy.h"
#include "GameScreen.h"


Enemy::Enemy(void)
{
	cooldownClock.restart();
	gravity = 1;
	direction = 1;
	x = -100;
	y = -100;
	xVelocity = 0;
	yVelocity = 0;
	spriteSheet.loadFromFile("images/entities/Enemy1.png");
	tileChunk = sf::Rect<int>(0,0,32,32);
	myTexture.loadFromImage(spriteSheet, tileChunk);
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(16,32);
}

void Enemy::update(ActionList _actionList) {
	bool onGround = false;
	if ((GameScreen::gameMap->getMapPos(((x+3)/32), ((y)/32)) == 1 || GameScreen::gameMap->getMapPos(((x-13)/32), ((y)/32)) == 1) && (y-1)/32 != (y+1)/32)
		onGround = true;

	
	// Move right
	if (_actionList.checkAction('r')) {
		if (!_actionList.checkAction('~')) {
			direction = 1;
			tileChunk.left = 0;
			myTexture.loadFromImage(spriteSheet, tileChunk);
		}
		if (xVelocity < 6)
			xVelocity++;
	}
	else if (xVelocity > 0 && !(_actionList.checkAction('l') || _actionList.checkAction('r')))
		xVelocity -= xVelocity/3;

	// Move left
	if (_actionList.checkAction('l')) {
		if (!_actionList.checkAction('~')) {
			direction = -1;
			tileChunk.left = 32;
			myTexture.loadFromImage(spriteSheet, tileChunk);
		}
		if (xVelocity > -6)
			xVelocity--;
	}
	else if (xVelocity < 0 && !(_actionList.checkAction('l') || _actionList.checkAction('r')))
		xVelocity -= xVelocity/3;

	// Jump
	if (_actionList.checkAction(' ') && onGround && yVelocity >= 0) {
		if (_actionList.checkAction('d')) {
			yVelocity = 9;
			onGround = false;
		}
		else {
			yVelocity = -8;
			onGround = false;
			tileChunk.top = 32;
			myTexture.loadFromImage(spriteSheet, tileChunk);
		}
	} else if (_actionList.checkAction(' ') && !onGround && yVelocity < -6) {
		gravity = 0.12;
	}

	// Shoot
	/*if (_actionList.checkAction('~') && canShootBullet) {
		shootBullet = true;
		canShootBullet = false;
		cooldownClock.restart();
		if (direction == 1)
			x -= 4;
		if (direction == -1)
			x += 4;
	}*/

	// Gravity
	if (!onGround && yVelocity < 9) {
		yVelocity += gravity;
		gravity = 1;
	} else if (onGround && yVelocity > 0){
		yVelocity = 0;
		if (GameScreen::gameMap->getMapPos((x/32), ((y)/32)) == 1 && (int)y % 32 != 0 && (int)y % 32 < 9) {
			y -= ((int)y % 32);
		}
		else if ((int)y % 32 != 0)
			y += (32 - ((int)y % 32));
		tileChunk.top = 0;
		myTexture.loadFromImage(spriteSheet, tileChunk);
	}
	
	x += xVelocity;
	y += yVelocity;
	mySprite.setPosition(x, y);
}

sf::Sprite Enemy::getSprite() {
	return mySprite;
}

void Enemy::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

float Enemy::get_x()
{
	return x;
}

float Enemy::get_y()
{
	return y;
}

Enemy::~Enemy(void)
{
}
