#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "CharacterData.h"

class Building {
public:
	Building(const CharacterData& data);
    virtual void update(sf::Time deltaTime);
    virtual void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
protected:
	AnimatedSprite buildingSprite;
};