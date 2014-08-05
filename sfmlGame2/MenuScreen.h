#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Screen.h"

class MenuScreen :
	public Screen
{
public:
	MenuScreen();
	void getInput(sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	~MenuScreen();

private:
	sf::Font _font;
	sf::Text MenuMessage;
};
