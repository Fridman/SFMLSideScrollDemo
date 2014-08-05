#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

Map * GameScreen::gameMap;

GameScreen::GameScreen(void)
{
	GameScreen::gameMap = new Map();
	player1.setPosition(100,100);
	gameMap->loadMap("level1.txt");
	gameMap->drawMap();
	for (int i = 0; i < 32; i++) {
		projectileList[i] = Projectile();
	}
}


void GameScreen::getInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
	}
	if (KEY_LEFT)
		myActionList.appendAction('l');
	if (KEY_RIGHT)
		myActionList.appendAction('r');
	if (KEY_SPACE)
		myActionList.appendAction(' ');
	if (KEY_CONTROL && ! player1.isShootBullet())
		myActionList.appendAction('~');
}

void GameScreen::update()
{
	player1.update(myActionList);
	myActionList.clearActions();
	if (player1.isShootBullet()) {
		for (int i = 0; i < 32; i++) {
			if (!projectileList[i].getInUse()) {
				projectileList[i].activate(player1.get_x()+(16 * player1.getDirection()), player1.get_y()-13, player1.getDirection());
				break;
			}
		}
	}
	for (int i = 0; i < 32; i++) {
		if (projectileList[i].getInUse()) {
			projectileList[i].update(myActionList);

		}
	}
	player1.clearShootBullet();
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.draw(gameMap->getSprite());
	window.draw(player1.getSprite());
	for (int i = 0; i < 32; i++) {
		if (projectileList[i].getInUse()) {
			window.draw(projectileList[i].getSprite());
		}
	}
}

GameScreen::~GameScreen(void)
{
}
