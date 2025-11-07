#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#include "DataClasses.h"
#include "Spritesheet.h"

class AnimatedSprite {
public:
	AnimatedSprite() = default;

	AnimatedSprite(const AnimatedSpriteData& data);

	void addTexture(const std::string& name);
	void setTexture(const std::string& textureName);

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window) const;

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);

	virtual void move(const sf::Vector2f& offset);
	virtual void scale(const sf::Vector2f& factors);
protected:
	const AnimatedSpriteData animatedSpriteData;
	std::string currentAnimation = "idle";

	std::unordered_map<std::string, Spritesheet> spritesheets;
	sf::Vector2f position{ 0.f, 0.f };
};