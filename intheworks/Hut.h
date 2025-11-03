#pragma once
#include <vector>

#include "Building.h"
#include "Orc.h"

class Hut : public Building {
	public:
	Hut();
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow& window) const override;
	std::vector<Orc>& getOrcs() { return orcs; }
private:
	std::vector<Orc> orcs;
	sf::Clock aiClock;
};