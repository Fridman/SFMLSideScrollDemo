#pragma once
#include "entity.h"
class Enemy :
	public Entity
{
public:
	bool shootBullet;
	bool canShootBullet;
	bool unactivate;
	void deactivate();
	bool newActions;
	bool isShootBullet();
	float getDirection();
	ActionList myActionList;
	Enemy(void);
	void update(ActionList _actionList) override;
	sf::Sprite getSprite() override;
	void activate(float _x, float _y);
	void hit(int i);
	bool isActivated();
	bool checkJump();
	bool checkLanding();
	bool checkPosRelative(int _x, int _y);
	int direction;
	float get_x();
	float get_y();
	void clearShootBullet();
	~Enemy(void);
private:
	sf::Texture textureStorage[4];
	bool hitCheck;
	bool activated;
	int healthPoints;
	float gravity;
	float x, y;
	float xVelocity;
	float yVelocity;
	sf::Clock cooldownClock;
	sf::Texture myTexture;
	sf::Sprite mySprite;
	sf::Rect<int> tileChunk;
	sf::Image spriteSheet;
};

