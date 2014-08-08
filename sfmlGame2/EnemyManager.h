#pragma once
#include "Enemy.h"
#include "ActionList.h"

class EnemyManager
{
public:
	EnemyManager(void);
	void update();
	Enemy * getEnemy(int i);

	~EnemyManager(void);

private:
	Enemy _enemies[32];

};

