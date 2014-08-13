#include "EnemyManager.h"
#include "GameScreen.h"
#include "Game.h"


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
			if (_enemies[i].unactivate)
				unactivate(i);
			aiRoutine(&_enemies[i]);
			_enemies[i].update(myActionList);
			myActionList.clearActions();
		} else {
			break;
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

void EnemyManager::unactivate(int i) {
	for (int k = i; k < 32; k++) {
		_enemies[k].deactivate();
		if (_enemies[k+1].isActivated() && k < 31) {
			_enemies[k] = _enemies[k+1];
		} else {
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
		float player_x = player1->get_x();
		float player_y = player1->get_y();
		float enemy_x = _enemy->get_x();
		float enemy_y = _enemy->get_y();
		if (player_x > enemy_x+200 || player_x > enemy_x && (_enemy->direction == -1 || !_enemy->checkLanding() || !IS_BETWEEN(player_y, enemy_y - 16, enemy_y + 16))) {
			myActionList.appendAction('r');
			if (_enemy->checkJump())
				myActionList.appendAction(' ');
		} if (player_x < enemy_x-200 || player_x < enemy_x && (_enemy->direction == 1 || !_enemy->checkLanding() || !IS_BETWEEN(player_y, enemy_y - 16, enemy_y + 16))) {
			myActionList.appendAction('l');
			if (_enemy->checkJump())
				myActionList.appendAction(' ');
		} if (IS_BETWEEN(player_x, enemy_x - 200, enemy_x + 200)) {
			if (enemy_y < player_y - 16) {
				myActionList.appendAction(' ');
				myActionList.appendAction('d');
			} else if (enemy_y > player_y + 16) {
				myActionList.appendAction(' ');
			} else if ((IS_BETWEEN(player_y, enemy_y - 16, enemy_y + 16))) {
				myActionList.appendAction('~');
			}
		}
	}
}

EnemyManager::~EnemyManager(void)
{
}
