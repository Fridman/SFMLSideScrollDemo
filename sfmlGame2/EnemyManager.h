#pragma once
#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "ActionList.h"

class EnemyManager
{
public:
	EnemyManager(void);
	EnemyManager(Player * _player);
	void update();
	Enemy * getEnemy(int i);
	void activate(float _x, float _y);
	~EnemyManager(void);

private:
	void unactivate(int i);
	void aiRoutine(Enemy * _enemy);
	int iUpdate;
	Player * player1;
	ActionList myActionList;
	Enemy _enemies[32];

};

