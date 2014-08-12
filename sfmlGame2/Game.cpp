#include "Game.h"
#include "SplashScreen.h"

sf::Font Game::_font;
std::shared_ptr<Screen> Game::screen = std::make_shared<SplashScreen>();

Game::Game()
{
	game_over = false;
	sprintf_s(ver,"0.0.1");
	sprintf_s(title,"Game %s", ver);
	_font.loadFromFile("fonts/arial.ttf");
}

void Game::run()
{
	sf::Clock clock1;
	sf::Clock clock2;
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), title);

	printf("Running Game\n");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
		}

		if (game_over) {
			window.close();
		}

		elapsed = clock1.getElapsedTime();
		// Render section of the game loop
		if (elapsed.asSeconds() >= (0.02)) {
			//Lock game speed.
			//Take input here
			Game::screen->getInput(window);
			//Update logic here.
			Game::screen->update();
			clock1.restart();

		}
		elapsed = clock2.getElapsedTime();
		if (elapsed.asSeconds() >= (/*1/fpsMax*/ 0/02)) {
			//Set up FPS counter.
			//Lock render speed.	
			fps = float(1)/elapsed.asSeconds();
			clock2.restart();
			render(window);

		}
		else {
			sf::Time sleeptime = sf::Time(sf::seconds(((1/fpsMax) - elapsed.asSeconds())*0.5));
			sf::sleep(sleeptime);
		}
	}
}

void Game::render(sf::RenderWindow &window) {
	window.clear();
	Game::screen->render(window);
	window.display();
}


Game::~Game()
{
}
