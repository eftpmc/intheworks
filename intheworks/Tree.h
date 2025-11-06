#pragma once
#include "GameObject.h"

class Tree : public ResourceObject {
public:
    Tree(const AnimatedSpriteData& spriteData, const sf::Vector2f& pos, const std::string resourceName, const int resourceAmount) : ResourceObject(spriteData, resourceName, resourceAmount) {
        sprite.addTexture("idle");
        sprite.addTexture("cut");
        sprite.setTexture("idle");

        sprite.setPosition(pos);
        position = pos;
        name = "Tree";
    }

    void update(sf::Time deltaTime) override {
        sprite.update(deltaTime);
    }

    void draw(sf::RenderWindow& window) const override {
        sprite.draw(window);
    }

    std::string getType() const override { return "Tree"; }
};
