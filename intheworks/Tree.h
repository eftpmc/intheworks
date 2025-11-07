#pragma once
#include "GameObject.h"

class Tree : public ResourceObject {
public:
    Tree(const AnimatedSpriteData& spriteData, const std::string resourceName, const int resourceAmount) : ResourceObject(spriteData, resourceName, resourceAmount) {
        sprite.addTexture("idle", 0);
        sprite.addTexture("cut", 0);
        sprite.addTexture("shake", 0);
        sprite.setTexture("idle");

        name = "Tree";
    }

    void update(sf::Time deltaTime) override {
        sprite.update(deltaTime);
    }

    void draw(sf::RenderWindow& window) const override {
        sprite.draw(window);
    }

    std::unique_ptr<GameObject> clone() const override {
        return std::make_unique<Tree>(*this);
    }

    std::string getType() const override { return "Tree"; }
};
