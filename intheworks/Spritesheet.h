#pragma once
#include <SFML/Graphics.hpp>

#include "DataClasses.h"

class Spritesheet {
public:
	Spritesheet();

	void update(sf::Time deltaTime, const AnimatedSpriteData& data);
	void draw(sf::RenderWindow& window) const;

	void setTexture(const std::string& textureName, int layer, const AnimatedSpriteData& data);

	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	void setPosition(const sf::Vector2f& position);
	void move(const sf::Vector2f& offset);
	void scale(const sf::Vector2f& factors);
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rectSourceSprite;

	float elapsedTime = 0.f;
};