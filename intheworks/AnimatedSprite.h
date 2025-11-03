#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#include "CharacterData.h"

class AnimatedSprite {
public:
	AnimatedSprite(const CharacterData& data);

	void addAnimation(const std::string& name);

	void update(sf::Time deltaTime, const std::string& animationName);
	void draw(sf::RenderWindow& window) const;

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);

	void move(const sf::Vector2f& offset);
	void scale(const sf::Vector2f& factors);
protected:
	const CharacterData characterData;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rectSourceSprite;

	std::unordered_map<std::string, sf::Texture> animations;
	float elapsedTime = 0.f;
};