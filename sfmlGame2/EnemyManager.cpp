#include "EnemyManager.h"


EnemyManager::EnemyManager(void)
{
	for (int i = 0; i < 32; i++) {
		_enemies[i] = Enemy();
	}
}


EnemyManager::~EnemyManager(void)
{
}
