#include "Hut.h"

Hut::Hut() : Building(CharacterData("hut", 148, 148, 148, 0, 148, 0.f))
{
	buildingSprite.setPosition({ 900.f, 720.f / 2.f });
	buildingSprite.scale({ 1.f, 1.f });
	buildingSprite.addAnimation("idle");
}

void Hut::update(sf::Time deltaTime)
{
	Building::update(deltaTime);
	if (aiClock.getElapsedTime().asSeconds() > 10.f)
	{
		Orc newOrc;
		newOrc.setPosition({ buildingSprite.getPosition().x, buildingSprite.getPosition().y + 40.f });
		orcs.push_back(newOrc);
		aiClock.restart();
	}
	for (auto& orc : orcs)
	{
		orc.update(deltaTime);
	}
}

void Hut::draw(sf::RenderWindow& window) const
{
	Building::draw(window);
	for (const auto& orc : orcs)
	{
		orc.draw(window);
	}
}