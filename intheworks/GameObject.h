#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "DataClasses.h"
#include "AnimatedSprite.h"

class GameObject {
public:
    GameObject(const AnimatedSpriteData& spriteData)
        : sprite(spriteData) {

        bounds = sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(static_cast<float>(spriteData.size.x), static_cast<float>(spriteData.size.y)));
    }
    virtual ~GameObject() = default;

	AnimatedSprite sprite;
    sf::Vector2f position;
    sf::FloatRect bounds;
    std::string name;
    bool isActive = true;

    virtual void update(sf::Time deltaTime) {}
    virtual void draw(sf::RenderWindow& window) const {}
    virtual std::string getType() const { return "GameObject"; }
    virtual void setTexture(std::string textureName) {
		sprite.setAnimation(textureName);
    }
};

class ResourceObject : public GameObject {
public:
    ResourceObject(const AnimatedSpriteData& spriteData, std::string resource, int resourceAmount) : GameObject(spriteData), resourceType(resource), maxResources(resourceAmount), currentResources(resourceAmount) {
	}
	int maxResources = 0;
	int currentResources = 0;
	std::string resourceType;
    virtual void harvest(int amount) {
		currentResources = std::max(0, currentResources - amount);
        if(currentResources == 0) {
            isActive = false;
			std::cout << name << " has been depleted." << std::endl;
		}
    }
};

class Tree : public ResourceObject {
public:
    Tree(const AnimatedSpriteData& spriteData, const sf::Vector2f& pos, const std::string resourceName, const int resourceAmount) : ResourceObject(spriteData, resourceName, resourceAmount) {
		sprite.addAnimation("idle");
        sprite.addAnimation("cut");
		sprite.setAnimation("idle");

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
