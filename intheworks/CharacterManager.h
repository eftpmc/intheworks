#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

#include "Character.h"

class CharacterManager {
public:
	CharacterManager();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window) const;
	void createCharacter(std::string characterName, sf::Vector2f pos);
	std::vector<Character*> getCharacters();
	std::vector<Character*> queryArea(const sf::Vector2f& pos, const sf::Vector2f& size);
protected:
	std::unordered_map<std::string, std::vector<std::unique_ptr<Character>>> characters;
	std::unordered_map<std::string, std::unique_ptr<Character>> defaultCharacters;
};