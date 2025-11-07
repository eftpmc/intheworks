#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(const AnimatedSpriteData& data)
	: animatedSpriteData(data)
{
}

void AnimatedSprite::addTexture(const std::string& name)
{
	spritesheets[name].setTexture(name, animatedSpriteData);
}

void AnimatedSprite::setTexture(const std::string& textureName)
{
	currentAnimation = textureName;
}

void AnimatedSprite::update(sf::Time deltaTime)
{
	spritesheets[currentAnimation].setPosition(position);
	spritesheets[currentAnimation].update(deltaTime, animatedSpriteData);
}

void AnimatedSprite::draw(sf::RenderWindow& window) const {
	spritesheets.at(currentAnimation).draw(window);
}

sf::Vector2f AnimatedSprite::getPosition() const
{
	return position;
}

void AnimatedSprite::setPosition(const sf::Vector2f& pos) {
	position = pos;
	for (auto& [_, sheet] : spritesheets)
		sheet.setPosition(position);
}

void AnimatedSprite::move(const sf::Vector2f& offset) {
	position += offset;
	for (auto& [_, sheet] : spritesheets)
		sheet.setPosition(position);
}

void AnimatedSprite::scale(const sf::Vector2f& factors) {
	for (auto& [name, sheet] : spritesheets)
		sheet.scale(factors);
}