#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Screen.h"

/*	Menuscreen implements the screen abstract class. The idea is to create 
	separate environments for which the entities tcan interact. For example, the
	entities utilized on a menu screen are going to interact differently than the
	entities utilized during gameplay even if they are the same objects (e.g. buttons).
*/

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
