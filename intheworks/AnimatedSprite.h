#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AnimatedSprite {
public:
	AnimatedSprite(const std::string& textureName);

	void addAnimation(const std::string& name);

	void update(sf::Time deltaTime, const int& state);
	void draw(sf::RenderWindow& window) const;

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);

	void move(const sf::Vector2f& offset);
	void scale(const sf::Vector2f& factors);
protected:
	std::string textureName;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rectSourceSprite;

	std::unordered_map<std::string, sf::Texture> animations;
	float elapsedTime = 0.f;
};