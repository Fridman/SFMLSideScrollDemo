#include "Enemy.h"
#include "GameScreen.h"


Enemy::Enemy(void)
{
	cooldownClock.restart();
	shootBullet = false;
	canShootBullet = false;
	unactivate = false;
	hitCheck = false;
	activated = false;
	gravity = 1;
	direction = 1;
	x = -100;
	y = -100;
	xVelocity = 0;
	yVelocity = 0;
	healthPoints = 0;
}

void Enemy::update(ActionList _actionList)
	// Updates the enemy logic given the instructions decided in the manager.
{
	if (!canShootBullet && cooldownClock.getElapsedTime().asSeconds() > 0.5) {
		canShootBullet = true;
		cooldownClock.restart();
	}
	if (activated) {
		bool onGround = false;
		if ((GameScreen::gameMap->getMapPos(((x+3)/32), ((y+16)/32)) == 1 || GameScreen::gameMap->getMapPos(((x-13)/32), ((y+16)/32)) == 1) && ((int)y-5)/32 != ((int)y+5)/32)
			onGround = true;

	
		// Move right
		if (_actionList.checkAction('r')) {
			if (!_actionList.checkAction('~')) {
				if (direction != 1) {
					direction = 1;
					myTexture = textureStorage[0];
				}
			}
			if (xVelocity < 4)
				xVelocity++;
		}
		else if (xVelocity > 0 && !(_actionList.checkAction('l') || _actionList.checkAction('r')))
			xVelocity -= xVelocity/3;

		// Move left
		if (_actionList.checkAction('l')) {
			if (!_actionList.checkAction('~')) {
				if (direction != -1) {
					direction = -1;
					myTexture = textureStorage[1];
				}
			}
			if (xVelocity > -4)
				xVelocity--;
		}
		else if (xVelocity < 0 && !(_actionList.checkAction('l') || _actionList.checkAction('r')))
			xVelocity -= xVelocity/3;

		// Jump
		if (_actionList.checkAction(' ') && onGround && yVelocity >= 0) {
			if (direction == 1)
				myTexture = textureStorage[2];
			else if (direction == -1)
				myTexture = textureStorage[3];
			if (_actionList.checkAction('d')) {
				yVelocity = 9;
				onGround = false;
			}
			else {
				yVelocity = -8;
				onGround = false;
			}
		} else if (_actionList.checkAction(' ') && !onGround && yVelocity < -6) {
			gravity = 0.12;
		}

		// Shoot
		if (_actionList.checkAction('~') && canShootBullet) {
			shootBullet = true;
			canShootBullet = false;
			if (direction == 1)
				x -= 4;
			if (direction == -1)
				x += 4;
		}

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
		}

		if (healthPoints <= 0) {
			unactivate = true;;
		}
		if (GameScreen::gameMap->getMapPos(((x)/32), ((y)/32)) == -1) {
			unactivate = true;;
		}
		
		if (!hitCheck)
			mySprite.setColor(sf::Color::White);
		if (hitCheck)
			hitCheck = false;

	} 
	if (!activated) {
		x = -1000;
		y = -1000;
	}
	x += xVelocity;
	y += yVelocity;
	mySprite.setPosition(x, y);
}

sf::Sprite Enemy::getSprite() {
	// Returns the value of the sprite contained by the Enemy object.
	return mySprite;
}

void Enemy::activate(float _x, float _y)
	// Sets an enemy to a state such that they are involved in the game logic. Otherwise, they are stored offscreen.
{
	cooldownClock.restart();
	spriteSheet.loadFromFile("images/entities/Enemy1.png");
	tileChunk = sf::Rect<int>(0,0,32,32);
	textureStorage[0].loadFromImage(spriteSheet, tileChunk);
	tileChunk.left = 32;			
	textureStorage[1].loadFromImage(spriteSheet, tileChunk);
	tileChunk.left = 0;
	tileChunk.top = 32;		
	textureStorage[2].loadFromImage(spriteSheet, tileChunk);
	tileChunk.left = 32;
	tileChunk.top = 32;		
	textureStorage[3].loadFromImage(spriteSheet, tileChunk);
	myTexture = textureStorage[0];
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(16,32);
	activated = true;
	x = _x;
	y = _y;
	healthPoints = 10;
}

float Enemy::get_x()
	// Returns the x-coordinate.
{
	return x;
}

float Enemy::get_y()
	// Returns the y-coordinate.
{
	return y;
}

bool Enemy::isActivated() {
	// Returns whether the enemy has been activated or not.
	return activated;
}

void Enemy::deactivate() {
	// Returns whether the enemy has been activated or not.
	activated = false;
	unactivate = false;
}

void Enemy::hit(int i)
	// Updates the enemy logic for recieving damage.
{
	hitCheck = true;
	healthPoints -= i;
	mySprite.setColor(sf::Color::Red);
}

float Enemy::getDirection()
{
	return direction;
}

bool Enemy::isShootBullet()
{
	return shootBullet;
}

void Enemy::clearShootBullet()
{
	shootBullet = false;
}

bool Enemy::checkJump()
	// Returns whether the enemy is at the edge of a platform. This is used in the EnemyManager::aiRoutine function.
{
	return GameScreen::gameMap->getMapPos(((int)x/32)+direction, ((int)y/32)) == 0;
}

bool Enemy::checkLanding()
	// Checks whether there is a platform below the enemy. This is used in the EnemyManager::aiRoutine function.
{
	return GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+1) == 1 ||
		GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+2) == 1 ||
		GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+3) == 1 ||
		GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+4) == 1;
}

bool Enemy::checkPosRelative(int _x, int _y)
{
	return GameScreen::gameMap->getMapPos(((int)x/32)+_x, ((int)y/32)+_y) == 1;
}

Enemy::~Enemy(void)
{
}
