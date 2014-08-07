#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Screen.h"
#include "Player.h"
#include "Map.h"
#include "Projectile.h"

/*	Game screen implements the screen abstract class. The idea is to create 
	separate environments for which the entities tcan interact. For example, the
	entities utilized on a menu screen are going to interact differently than the
	entities utilized during gameplay even if they are the same objects (e.g. buttons).
*/

class GameScreen :
	public Screen
{
public:
	GameScreen(void);
	void getInput(sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	~GameScreen(void);
	
	static Map * gameMap;

private:
	ActionList myActionList;
	Player player1;
	Projectile projectileList[32];
};
