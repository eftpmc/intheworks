#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

class Character {
public:
    Character(const std::string& textureName, float moveSpeed);
    virtual void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
protected:
    AnimatedSprite characterSprite;
    int facing = 1;
	int state = 1; // 1: idle, 2: walk
    sf::Vector2f velocity;
    float speed;
};
