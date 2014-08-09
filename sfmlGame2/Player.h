#pragma once
#include "entity.h"
#include "ActionList.h"

class Player :
	public Entity
{
public:
	Player(void);
	sf::Sprite getSprite() override;
	void update(ActionList _actionList) override;
	void setPosition(float _x, float _y);
	void clearShootBullet();
	bool isShootBullet();
	float get_x();
	float get_y();
	float getDirection();
	bool dead;
	~Player(void);
private:
	bool shootBullet;
	bool canShootBullet;
	float gravity;
	int direction;
	float x, y;
	float xVelocity;
	float yVelocity;
	sf::Clock cooldownClock;
	sf::Texture myTexture;
	sf::Sprite mySprite;
	sf::Rect<int> tileChunk;
	sf::Image spriteSheet;
};


