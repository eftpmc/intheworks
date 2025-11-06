#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#include "DataClasses.h"

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

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rectSourceSprite;

	std::unordered_map<std::string, sf::Texture> textures;
	float elapsedTime = 0.f;
	int facing = 1;
};