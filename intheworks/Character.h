#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "CharacterData.h"

class Character {
public:
    Character(const CharacterData& data);
    virtual void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    void toggleSprint();
protected:
    AnimatedSprite characterSprite;
    int facing = 1;
	int state = 1; // 1: idle, 2: walk
    sf::Vector2f velocity;
    float speed;
    bool isSprinting = false;
};
