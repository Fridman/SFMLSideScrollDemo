#pragma once
#include "entity.h"
class Enemy :
	public Entity
{
public:
	Enemy(void);
	void update(ActionList _actionList) override;
	sf::Sprite getSprite() override;
	void setPosition(float _x, float _y);
	float get_x();
	float get_y();
	~Enemy(void);
private:
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

