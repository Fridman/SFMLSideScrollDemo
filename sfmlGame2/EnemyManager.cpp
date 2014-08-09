#include "EnemyManager.h"


EnemyManager::EnemyManager(void)
{
	myActionList = ActionList();
	for (int i = 0; i < 32; i++) {
		_enemies[i] = Enemy();
	}
}

EnemyManager::EnemyManager(Player * _player)
{
	player1 = _player;
	myActionList = ActionList();
	for (int i = 0; i < 32; i++) {
		_enemies[i] = Enemy();
	}
}

void EnemyManager::update()
{
	for (int i = 0; i < 32; i++) {
		if (_enemies[i].isActivated()) {
			aiRoutine(&_enemies[i]);
			_enemies[i].update(myActionList);
			myActionList.clearActions();
		}
	}
}

void EnemyManager::activate(float _x, float _y)
	//Activated a dormant enemy and places it in the game space.
{
	for (int i = 0; i < 32; i++) {
		if (!_enemies[i].isActivated()) {
			_enemies[i].activate(_x, _y);
			break;
		}
	}
}

Enemy * EnemyManager::getEnemy(int i)
{
	return &_enemies[i];
}

void EnemyManager::aiRoutine(Enemy * _enemy)
{
	if (player1 != NULL) {
		if (player1->get_x() > _enemy->get_x()) {
			if (player1->get_x() > _enemy->get_x()+200 || _enemy->direction == -1 || !_enemy->checkLanding()) {
				myActionList.appendAction('r');
				if (_enemy->checkJump())
					myActionList.appendAction(' ');
			}
		} else if (player1->get_x() < _enemy->get_x()) {
			if (player1->get_x() < _enemy->get_x()-200 || _enemy->direction == 1 || !_enemy->checkLanding()) {
				myActionList.appendAction('l');
				if (_enemy->checkJump())
					myActionList.appendAction(' ');
			}
		}
	}
}

EnemyManager::~EnemyManager(void)
{
}
