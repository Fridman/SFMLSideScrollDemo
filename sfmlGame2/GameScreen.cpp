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
	player1.setPosition(100,100);
	gameMap->loadMap("level1.txt");
	gameMap->drawMap();
	for (int i = 0; i < 32; i++) {
		projectileList[i] = Projectile();
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
		for (int i = 0; i < 32; i++) {
			if (!projectileList[i].getInUse()) {
				projectileList[i].activate(player1.get_x()+(16 * player1.getDirection()), player1.get_y()-12 + ((rand() % 5) - 3), player1.getDirection());
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
	//	Render draws all of the game objects to the window.
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
	//	The destructor is empty for now.
{
}
