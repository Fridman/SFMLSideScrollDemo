#pragma once
#include "entity.h"
class Projectile :
	public Entity
{
public:
	Projectile(void);
	sf::Sprite getSprite() override;
	void update(ActionList _actionList) override;
	void activate(float _x, float _y, int _direction);
	void setDirection(int dir);
	bool getInUse();
	~Projectile(void);

private:
	bool reversed;
	sf::Clock lifeClock;
	sf::Image loadImage;
	bool inUse;
	float x, y;
	int direction;
	sf::Texture myTexture;
	sf::Sprite mySprite;
};

