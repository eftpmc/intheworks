#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "Character.h"

struct Resources {
	int food = 0;
	int wood = 0;
	int stone = 0;
};

class Clan {
	public:
		Clan();
		void update(sf::Time deltaTime);
		void draw(sf::RenderWindow& window) const;
		std::vector<Character>& getMembers() { return members; }
private:
	std::vector<Character> members;

	Resources resources;
};