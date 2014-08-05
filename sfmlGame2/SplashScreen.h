#pragma once
#include "screen.h"
class SplashScreen :
	public Screen
{
public:
	SplashScreen(void);
	void getInput(sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	~SplashScreen(void);
};

