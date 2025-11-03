#include "Building.h"

Building::Building(const CharacterData& data) : buildingSprite(data)
{
}

void Building::update(sf::Time deltaTime)
{
	buildingSprite.update(deltaTime, "idle");
}

void Building::draw(sf::RenderWindow& window) const
{
	buildingSprite.draw(window);
}