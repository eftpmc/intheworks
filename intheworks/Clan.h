#pragma once

#include "Map.h"

class Clan {
public:
	Clan(Map* map);
	void update(sf::Time deltaTime);
	void addMember(Character* character);
	void chopTree();
protected:
	std::vector<Character*> members;
	std::vector<GameObject*> assigned;
	Map* map;
};