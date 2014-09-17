#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

/*	Game screen implements the screen abstract class. The idea is to create 
	separate environments for which the entities tcan interact. For example, the
	entities utilized on a menu screen are going to interact differently than the
	entities utilized during gameplay even if they are the same objects (e.g. buttons).
*/

Map * GameScreen::gameMap;

GameScreen::GameScreen(void)
	// Constructor loads the map information from a text document an prepares the gameplay objects.
{
	GameScreen::gameMap = new Map();
	spawnTimer.restart();
	screenView.reset(sf::FloatRect(0, 0, Game::window_x, Game::window_y));
	_enemyManager = EnemyManager(&player1);
	player1.setPosition(100,100);
	gameMap->loadMap("level1.txt");
	gameMap->drawMap();
	for (int i = 0; i < 128; i++) {
		projectileList[i] = Projectile(&_enemyManager, &player1);
	}
}


void GameScreen::getInput(sf::RenderWindow& window)
	//	GetInput takes input from the user and stores it in a list.
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
	}
	if (KEY_LEFT)
		myActionList.appendAction('l');
	if (KEY_RIGHT)
		myActionList.appendAction('r');
	if (KEY_DOWN)
		myActionList.appendAction('d');
	if (KEY_UP)
		myActionList.appendAction('u');
	if (KEY_SPACE)
		myActionList.appendAction(' ');
	if (KEY_CONTROL && ! player1.isShootBullet())
		myActionList.appendAction('~');
}

void GameScreen::update()
	//	update takes the list of user input and passes it to the player entity.
	//	The player entity takes the list and performs all the required actions.
	//	The action list is cleared for the next cycle.
	//	Additionally, the other objects also update their data for this cycle.
{
	player1.update(myActionList);
	myActionList.clearActions();
	if (player1.isShootBullet()) {
		int startX = 16 * player1.getDirection();
		for (int i = 0; i < 128; i++) {
			if (!projectileList[i].getInUse()) {
				projectileList[i].activate(player1.get_x(), player1.get_y()-12, player1.getShotDirection(), 0);
				break;
			}
		}
	}
	for (int i = 0; i < 32; i++) {
		if (_enemyManager.getEnemy(i)->isShootBullet()) {
		for (int k = 0; k < 128; k++) {
			if (!projectileList[k].getInUse()) {
				projectileList[k].activate(_enemyManager.getEnemy(i)->get_x()+(16 * _enemyManager.getEnemy(i)->getDirection()), _enemyManager.getEnemy(i)->get_y()-12 + ((rand() % 5) - 3), _enemyManager.getEnemy(i)->getDirection(), 1);
				_enemyManager.getEnemy(i)->clearShootBullet();
				break;
			}
		}
		}
		if (projectileList[i].getInUse()) {
			projectileList[i].update(myActionList);

		}
	}
	player1.clearShootBullet();
	if (spawnTimer.getElapsedTime().asSeconds() > 10) {
		for (int i = 0; i < rand() % 5; i++) 
			_enemyManager.activate(rand() % 2048, 16);
		printf("spawning dude!\n");
		spawnTimer.restart();
	}
	_enemyManager.update();
	if (player1.dead)
		Game::screen = std::make_shared<MenuScreen>();
}

void GameScreen::render(sf::RenderWindow& window)
	//	Render draws all of the game objects to the window.
{
	int center_x = window.getView().getCenter().x;
	int center_y = window.getView().getCenter().y;
	if (window.getView().getCenter().x < 1568 && player1.get_x() > window.getView().getCenter().x + 200)
		center_x += 1;
	if (window.getView().getCenter().x > 480 && player1.get_x() < window.getView().getCenter().x - 200)
		center_x -= 1;
	if (window.getView().getCenter().y > 360 && player1.get_y() < window.getView().getCenter().y - 200)
		center_y -= 1;
	if (window.getView().getCenter().y < 1688 && player1.get_y() > window.getView().getCenter().y + 200)
		center_y += 1;
	screenView.reset(sf::FloatRect(center_x - (Game::window_x/2), center_y - (Game::window_y/2), Game::window_x, Game::window_y));
	window.setView(screenView);
	window.draw(gameMap->getSprite());
	window.draw(player1.getSprite());
	for (int i = 128; i >= 0; i--) {
		if (projectileList[i].getInUse()) {
			window.draw(projectileList[i].getSprite());
		}
		if (i < 32)
			if (_enemyManager.getEnemy(i)->isActivated()) {
				window.draw(_enemyManager.getEnemy(i)->getSprite());
			}
	}
}

GameScreen::~GameScreen(void)
	//	The destructor is empty for now.
{
}
