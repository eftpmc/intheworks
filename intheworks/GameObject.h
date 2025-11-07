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
		sprite.setTexture(textureName);
    }
    virtual void setPosition(sf::Vector2f pos) {
        sprite.setPosition(pos);
        position = pos;
    }
    virtual std::unique_ptr<GameObject> clone() const = 0;
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
		}
    }
};