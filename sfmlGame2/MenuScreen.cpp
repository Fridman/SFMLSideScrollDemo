
#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

/*	Menuscreen implements the screen abstract class. The idea is to create 
	separate environments for which the entities tcan interact. For example, the
	entities utilized on a menu screen are going to interact differently than the
	entities utilized during gameplay even if they are the same objects (e.g. buttons).
*/

MenuScreen::MenuScreen()
{
	_font.loadFromFile("fonts/arial.ttf");
	MenuMessage.setString("Welcome to the game!\nPress enter to start!");
	MenuMessage.setOrigin(75, 75);
	MenuMessage.setPosition(Game::window_x/2, Game::window_y/2);
	MenuMessage.setFont(_font);
	MenuMessage.setCharacterSize(16);
	MenuMessage.setColor(sf::Color::Red);
}

void MenuScreen::getInput(sf::RenderWindow& window) {
	if (KEY_ENTER)
		Game::screen = std::make_shared<GameScreen>();
}

void MenuScreen::update() {
}

void MenuScreen::render(sf::RenderWindow& window) {
	window.draw(MenuMessage);
}

MenuScreen::~MenuScreen(void)
{
}
