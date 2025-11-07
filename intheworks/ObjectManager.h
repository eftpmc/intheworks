#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

#include "GameObject.h"

class ObjectManager {
public:
	ObjectManager();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window) const;
	void createObject(std::string objectName, sf::Vector2f pos);
	std::vector<GameObject*> queryArea(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& type = "");
protected:
	std::unordered_map<std::string, std::vector<std::unique_ptr<GameObject>>> objects;
	std::unordered_map<std::string, std::unique_ptr<GameObject>> defaultObjects;
};