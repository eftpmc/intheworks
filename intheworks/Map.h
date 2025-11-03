#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Character.h"

class Map {
public:
	Map();
	void draw(sf::RenderWindow& window) const;
	void update(sf::Time& deltaTime);
protected:
	sf::Texture texture;
	sf::IntRect rectSourceSprite;

	std::vector<sf::Sprite> mapTiles;
	std::ifstream infile;

	std::vector<Character> characters;

	Character orc = Character(CharacterData("orc", 600, 100, 100, 0, 100, 20.f));
};