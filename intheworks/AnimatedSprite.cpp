#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const std::string& textureName)
	: textureName(textureName), sprite(texture), rectSourceSprite(sf::Vector2(48, 48), sf::Vector2(32, 32))
{
	sprite.setTextureRect(rectSourceSprite);
	sprite.setOrigin({ sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2 });
}

void AnimatedSprite::addAnimation(const std::string& name)
{
	if (!texture.loadFromFile(textureName + "_" + name + ".png", false))
	{
		// error...
	}

	animations[name] = texture;
}

void AnimatedSprite::update(sf::Time deltaTime, const int& state)
{
	if(elapsedTime > .15f)
	{
		rectSourceSprite.position.x += 128;
		if (rectSourceSprite.position.x >= 1280)
		{
			rectSourceSprite.position.x = 48;
		}
		sprite.setTextureRect(rectSourceSprite);
		elapsedTime = 0.f;
	}

	elapsedTime += deltaTime.asSeconds();

	if(state == 1)
	{
		sprite.setTexture(animations["idle"]);
	}else if(state == 2)
	{
		sprite.setTexture(animations["walk"]);
	}
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