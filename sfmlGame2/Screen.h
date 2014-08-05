#pragma once

#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual void getInput(sf::RenderWindow& window) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};
