#include "SplashScreen.h"
#include "MenuScreen.h"
#include "Game.h"


SplashScreen::SplashScreen(void)
{
}

void SplashScreen::getInput(sf::RenderWindow& window) {
}

void SplashScreen::update() {
		Game::screen = std::make_shared<MenuScreen>();
}

void SplashScreen::render(sf::RenderWindow& window) {
}

SplashScreen::~SplashScreen(void)
{
}
