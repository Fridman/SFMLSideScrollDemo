#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stddef.h>
#include <string>
#include <sys/stat.h>
#include <direct.h>
#include <memory>

#include "Screen.h"

#define KEY_LEFT (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
#define KEY_RIGHT (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
#define KEY_DOWN (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
#define KEY_UP (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
#define KEY_SPACE (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
#define KEY_CONTROL ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
#define KEY_ENTER (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
#define IS_BETWEEN(a, b, c) (a > b && a < c)


class Game
{
public:
	Game();
	void run();
	void handleInput();
	void render(sf::RenderWindow& window);

	static const int fpsMax = 60;
	static const int window_x = 960;
	static const int window_y = 720;

	bool game_over;

	int fps;

	char ver[256];
	char title[256];
	
	sf::Time elapsed;

	static std::shared_ptr<Screen> screen;
	static sf::Font _font;


	~Game();
};