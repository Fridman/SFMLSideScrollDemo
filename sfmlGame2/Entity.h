#pragma once
#include <SFML/Graphics.hpp>
#include "ActionList.h"

class Entity
{
public:
	virtual sf::Sprite getSprite() = 0;
	virtual void update(ActionList _actionList) = 0;
};

