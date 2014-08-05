#include "Player.h"
#include "GameScreen.h"
#include "Map.h"


Player::Player(void)
{
	cooldownClock.restart();
	shootBullet = false;
	canShootBullet = true;
	gravity = 1;
	direction = 1;
	x = 100;
	y = 100;
	xVelocity = 0;
	yVelocity = 0;
	spriteSheet.loadFromFile("images/entities/Player.png");
	tileChunk = sf::Rect<int>(0,0,32,32);
	myTexture.loadFromImage(spriteSheet, tileChunk);
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(16,32);
}

void Player::update(ActionList _actionList)
{
	if (!canShootBullet && cooldownClock.getElapsedTime().asSeconds() > 0.2) {
		canShootBullet = true;
		cooldownClock.restart();
	}
	bool onGround = false;
	if (GameScreen::gameMap->getMapPos((x/32), ((y+5)/32)) == 1 && GameScreen::gameMap->getMapPos((x/32), ((y-5)/32)) == 0)
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
			yVelocity = 6;
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
	if (_actionList.checkAction('~') && canShootBullet) {
		shootBullet = true;
		canShootBullet = false;
		cooldownClock.restart();
	}

	// Gravity
	if (!onGround && yVelocity < 9) {
		yVelocity += gravity;
		gravity = 1;
	} else if (onGround && yVelocity > 0){
		yVelocity = 0;
		if (GameScreen::gameMap->getMapPos((x/32), ((y)/32)) == 1 && (int)y % 32 != 0) {
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

void Player::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Player::clearShootBullet()
{
	shootBullet = false;
}

sf::Sprite Player::getSprite()
{
	return mySprite;
}

float Player::get_x()
{
	return x;
}

float Player::get_y()
{
	return y;
}
float Player::getDirection()
{
	return direction;
}

bool Player::isShootBullet()
{
	return shootBullet;
}

Player::~Player(void)
{
}


