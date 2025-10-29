#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const CharacterData& data)
	: characterData(data),
	sprite(texture),
	rectSourceSprite(sf::Vector2(data.padding, data.padding), sf::Vector2(data.size, data.size))
{
	sprite.setTextureRect(rectSourceSprite);
	sprite.setOrigin({ sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2 });
}

void AnimatedSprite::addAnimation(const std::string& name)
{
	sf::Texture& tex = animations[name];

	if (!tex.loadFromFile(characterData.textureName + "_" + name + ".png", false))
	{
		// error...
	}
}

void AnimatedSprite::update(sf::Time deltaTime, const int& state)
{
	if(elapsedTime > .15f)
	{
		rectSourceSprite.position.x += characterData.stepPixels;
		if (rectSourceSprite.position.x >= characterData.width)
		{
			rectSourceSprite.position.x = characterData.padding;
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