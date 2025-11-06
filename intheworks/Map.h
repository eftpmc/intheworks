#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "DataClasses.h"
#include "Character.h"
#include "GameObject.h"
#include "Tree.h"

class Map {
public:
	Map();
	void draw(sf::RenderWindow& window) const;
	void update(sf::Time& deltaTime);

	std::vector<std::unique_ptr<GameObject>>& getObjects() { return objects; }
protected:
	sf::Texture texture;
	sf::IntRect rectSourceSprite;

	std::vector<sf::Sprite> mapTiles;
	std::ifstream infile;

	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<std::unique_ptr<Character>> characters;
};