#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const AnimatedSpriteData& data)
	: animatedSpriteData(data),
	sprite(texture),
	rectSourceSprite(sf::Vector2(data.padding, data.padding), sf::Vector2(data.size.x, data.size.y))
{
	sprite.setTextureRect(rectSourceSprite);
	sprite.setOrigin({ sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2 });
}

void AnimatedSprite::addAnimation(const std::string& name)
{
	sf::Texture& tex = animations[name];

	if (!tex.loadFromFile(animatedSpriteData.textureName + "_" + name + ".png", false))
	{
		// error...
	}
}

void AnimatedSprite::setAnimation(const std::string& animationName)
{
	sprite.setTexture(animations[animationName]);
}

void AnimatedSprite::update(sf::Time deltaTime)
{
	if(elapsedTime > animatedSpriteData.frameTime)
	{
		rectSourceSprite.position.x += animatedSpriteData.stepPixels;
		if (rectSourceSprite.position.x >= animatedSpriteData.width)
		{
			rectSourceSprite.position.x = animatedSpriteData.padding;
		}
		sprite.setTextureRect(rectSourceSprite);
		elapsedTime = 0.f;
	}

	elapsedTime += deltaTime.asSeconds();
}

void AnimatedSprite::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}	

sf::Vector2f AnimatedSprite::getPosition() const
{
	return sprite.getPosition();
}

void AnimatedSprite::setPosition(const sf::Vector2f& position) {
	sprite.setPosition(position);
}

void AnimatedSprite::move(const sf::Vector2f& offset)
{
	sprite.move(offset);
}

void AnimatedSprite::scale(const sf::Vector2f& factors)
{
	sprite.scale(factors);
}