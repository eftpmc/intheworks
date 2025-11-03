#include "House.h"

House::House() : Building(CharacterData("house", 128, 128, 128, 0, 128, 0.f))
{
	buildingSprite.setPosition({ 300.f, 720.f / 2.f });
	buildingSprite.scale({ 1.f, 1.f });
	buildingSprite.addAnimation("idle");
}

void House::update(sf::Time deltaTime)
{
	Building::update(deltaTime);
}

void House::draw(sf::RenderWindow& window) const
{
	Building::draw(window);
}