#include "Spritesheet.h"
#include <iostream>

Spritesheet::Spritesheet() : 
	sprite(texture),
	rectSourceSprite(sf::Vector2(0,0), sf::Vector2(0,0)) {
	sprite.setTextureRect(rectSourceSprite);
	sprite.setOrigin({ sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2 });
}

void Spritesheet::update(sf::Time deltaTime, const AnimatedSpriteData& data) {
	if (elapsedTime > data.frameTime)
	{
		rectSourceSprite.position.x += data.stepPixels;
		if (rectSourceSprite.position.x >= data.width)
		{
			rectSourceSprite.position.x = data.padding.x;
		}
		sprite.setTextureRect(rectSourceSprite);
		elapsedTime = 0.f;
	}

	elapsedTime += deltaTime.asSeconds();
}

void Spritesheet::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
}

void Spritesheet::setTexture(const std::string& textureName, int layer, const AnimatedSpriteData& data) {
	if (!texture.loadFromFile(data.textureName + "_" + textureName + std::to_string(layer) + ".png", false))
	{
		// error...
	}
	rectSourceSprite.position = sf::Vector2(data.padding.x, data.padding.y);
	rectSourceSprite.size = sf::Vector2(data.size.x, data.size.y);
	sprite.setTextureRect(rectSourceSprite);
	sprite.setTexture(texture);

	sprite.setOrigin(sf::Vector2f(data.size.x / 2.f, data.size.y / 2.f));
}

sf::Vector2f Spritesheet::getPosition() const
{
	return sprite.getPosition();
}

void Spritesheet::setPosition(const sf::Vector2f& position) {
	sprite.setPosition(position);
}

void Spritesheet::move(const sf::Vector2f& offset)
{
	sprite.move(offset);
}

void Spritesheet::scale(const sf::Vector2f& factors)
{
	sprite.setScale(factors);
}