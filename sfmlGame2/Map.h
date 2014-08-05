#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

class Map
{
public:
	Map(void);
	void loadMap(char fileName[64]);
	void drawMap();
	sf::Sprite getSprite();
	int getMapPos(int _x, int _y);
	~Map(void);
private:
	int map[64][64];
	sf::RenderTexture myTexture;
	sf::Sprite mySprite;
};

