#include "Map.h"
#include "Game.h"


Map::Map(void)
{
	for (int k = 0; k < 64; k++) {
		for (int i = 0; i < 64; i++) {
			map[i][k] = 0;
		}
	}
	myTexture.create(2048, 2048);
	mySprite.setPosition(0,0);
}

void Map::loadMap(char fileName[64])
{
	std::string line = "";
	char file_name[256];
	sprintf_s(file_name, "Levels/Level1.txt");
	std::ifstream sav (file_name);
	int i = 0;
	int k = 0;
	std::string temp;
	if (sav.is_open()) {
		while (sav.good()) {
			getline (sav, line);
			if (k >= 64)
				break;
			while (!line.empty()) {
				if (i >= 64)
					break;
				temp = line.substr(0, 1);
				if (temp == "0") {
					map[i][k] = 0;
				} else if (temp == "1") {
					map[i][k] = 1;
				}
				i++;
				line.erase(0, 1);
			}
			k++;
			i = 0;
		}
		sav.close();
	}
}

void Map::drawMap()
{
	int lastTexture = 0;
	sf::Image tileset;
	tileset.loadFromFile("images/tiles/testtile.png");
	sf::Rect<int> tileChunk = sf::Rect<int>(0,0,32,32);
	sf::Texture paintTexture;
	sf::Sprite paintSprite;
	paintTexture.loadFromImage(tileset, tileChunk);
	paintSprite.setTexture(paintTexture);
	for (int k = 0; k < 64; k++) {
		for (int i = 0; i < 64; i++) {
			if (lastTexture != map[i][k]) {
				if (map[i][k] == 0)
					tileChunk.top = 0;
				if (map[i][k] == 1)
					tileChunk.top = 32;
				paintTexture.loadFromImage(tileset, tileChunk);
				lastTexture = map[i][k];
				paintSprite.setTexture(paintTexture);
			}
			paintSprite.setPosition(i*32, k*32);
			myTexture.draw(paintSprite);
			myTexture.display();
		}
	}
	mySprite.setTexture(myTexture.getTexture());
}

sf::Sprite Map::getSprite()
{
	return mySprite;
}

int Map::getMapPos(int _x, int _y)
{
	return map[_x][_y];
}

Map::~Map(void)
{
}
