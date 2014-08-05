#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Screen.h"
#include "Player.h"
#include "Map.h"
#include "Projectile.h"

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
