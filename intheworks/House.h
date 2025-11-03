#pragma once
#include <vector>
#include "Building.h"
#include "CharacterData.h"

class House : public Building {
public:
	House();
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow& window) const override;
};