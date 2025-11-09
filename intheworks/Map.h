#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "DataClasses.h"
#include "CharacterManager.h"
#include "ObjectManager.h"

class Clan;

class Map {
public:
	Map();
	ObjectManager& getObjectManager() { return objectManager; }
	CharacterManager& getCharacterManager() { return characterManager; }
	void draw(sf::RenderWindow& window) const;
	void update(sf::Time& deltaTime);
protected:
	sf::Texture texture;
	sf::IntRect rectSourceSprite;

	std::vector<sf::Sprite> mapTiles;
	std::ifstream infile;

	ObjectManager objectManager;
	CharacterManager characterManager;
	Clan* clan;
};