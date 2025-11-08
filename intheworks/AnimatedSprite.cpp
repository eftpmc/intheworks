#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(const AnimatedSpriteData& data)
	: animatedSpriteData(data)
{
}

void AnimatedSprite::addTexture(const std::string& name, int layer)
{
	spritesheets[name][layer].setTexture(name, layer, animatedSpriteData);
}

void AnimatedSprite::setTexture(const std::string& textureName)
{
	currentAnimation = textureName;
}

void AnimatedSprite::update(sf::Time deltaTime)
{
	for (int i = 0; i < 3; i++) {
		spritesheets[currentAnimation][i].setPosition(position);
		spritesheets[currentAnimation][i].update(deltaTime, animatedSpriteData);
	}
}

void AnimatedSprite::draw(sf::RenderWindow& window) const {
	for (int i = 0; i < 3; i++) {
		spritesheets.at(currentAnimation)[i].draw(window);
	}
}

sf::Vector2f AnimatedSprite::getPosition() const
{
	return position;
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const {
	return spritesheets.at(currentAnimation)[0].getGlobalBounds();
}

void AnimatedSprite::setPosition(const sf::Vector2f& pos) {
	position = pos;
	for (auto& [_, sheet] : spritesheets)
		for (int i = 0; i < 3; i++) {
			sheet[i].setPosition(position);
		}
}

void AnimatedSprite::move(const sf::Vector2f& offset) {
	position += offset;
	for (auto& [_, sheet] : spritesheets)
		for (int i = 0; i < 3; i++) {
			sheet[i].setPosition(position);
		}
}

void AnimatedSprite::scale(const sf::Vector2f& factors) {
	for (auto& [name, sheet] : spritesheets)
		for (int i = 0; i < 3; i++) {
			sheet[i].scale(factors);
		}
}