#pragma once
#include "GameObject.h"

class Wood : public GameObject {
public:
    Wood(const AnimatedSpriteData& spriteData) : GameObject(spriteData) {
        sprite.addTexture("idle", 0);
        sprite.setTexture("idle");

        name = "Wood";
    }

    void update(sf::Time deltaTime) override {
        sprite.update(deltaTime);
    }

    void draw(sf::RenderWindow& window) const override {
        sprite.draw(window);
    }

    std::unique_ptr<GameObject> clone() const override {
        return std::make_unique<Wood>(*this);
    }

    std::string getType() const override { return "Wood"; }
};
