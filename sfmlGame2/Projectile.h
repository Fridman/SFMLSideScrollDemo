#pragma once
#include "Game.h"
#include "entity.h"
#include "EnemyManager.h"
#include "Enemy.h"

class Projectile :
	public Entity
{
public:
	Projectile(void);
	Projectile(EnemyManager * _enemyList, Player * _player1);
	sf::Sprite getSprite() override;
	void update(ActionList _actionList) override;
	void activate(float _x, float _y, int _direction, int _playerOrEnemy);
	void setDirection(int dir);
	bool getInUse();
	~Projectile(void);

private:
	Player * player1;
	int playerOrEnemy;
	EnemyManager * enemyList;
	bool reversed;
	sf::Clock lifeClock;
	sf::Image loadImage;
	bool inUse;
	float x, y;
	int direction;
	sf::Texture myTexture;
	sf::Sprite mySprite;
};

