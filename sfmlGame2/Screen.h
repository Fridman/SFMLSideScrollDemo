#pragma once

/*	This is the screen abstract class. The idea is to create 
	separate environments for which the entities tcan interact. For example, the
	entities utilized on a menu screen are going to interact differently than the
	entities utilized during gameplay even if they are the same objects (e.g. buttons).
*/

#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual void getInput(sf::RenderWindow& window) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};
