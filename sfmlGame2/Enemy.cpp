#include "Enemy.h"
#include "GameScreen.h"


Enemy::Enemy(void)
{
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
	if (activated) {
		bool onGround = false;
		if ((GameScreen::gameMap->getMapPos(((x+3)/32), ((y+16)/32)) == 1 || GameScreen::gameMap->getMapPos(((x-13)/32), ((y+16)/32)) == 1) && ((int)y-5)/32 != ((int)y+5)/32)
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

		if (healthPoints <= 0) {
			activated = false;
		}
		
		if (!hitCheck)
			mySprite.setColor(sf::Color::White);
		if (hitCheck)
			hitCheck = false;

	} else {
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
	myTexture.loadFromImage(spriteSheet, tileChunk);
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(16,32);
	activated = true;
	x = _x;
	y = _y;
	healthPoints = 10;
}

float Enemy::get_x()
{
	return x;
}

float Enemy::get_y()
{
	return y;
}

bool Enemy::isActivated() {
	return activated;
}

void Enemy::hit(int i)
{
	hitCheck = true;
	healthPoints -= i;
	mySprite.setColor(sf::Color::Red);
}

bool Enemy::checkJump()
{
	return GameScreen::gameMap->getMapPos(((int)x/32)+direction, ((int)y/32)) == 0;
}

bool Enemy::checkLanding()
{
	return GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+1) == 1 ||
		GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+2) == 1 ||
		GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+3) == 1 ||
		GameScreen::gameMap->getMapPos(((int)x/32), ((int)y/32)+4) == 1;
}

Enemy::~Enemy(void)
{
}
