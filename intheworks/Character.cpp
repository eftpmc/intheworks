#include "Character.h"

Character::Character(const CharacterData& data) 
	: characterSprite(data), speed(data.moveSpeed)
{
	characterSprite.setPosition({ 1000.f, 720.f / 2.f });
	characterSprite.addAnimation("idle");
	characterSprite.addAnimation("walk");
}

void Character::update(sf::Time deltaTime)
{
	std::string animation;
	if (velocity.x > 0.f || velocity.x < 0.f || velocity.y > 0.f || velocity.y < 0.f) {
		animation = "walk";
		characterSprite.move(velocity * speed * deltaTime.asSeconds());
	}
	else {
		animation = "idle";
	}

	characterSprite.update(deltaTime, animation);
}

void Character::draw(sf::RenderWindow& window) const
{
	characterSprite.draw(window);
}

sf::Vector2f Character::getPosition() const
{
	return characterSprite.getPosition();
}

void Character::setPosition(const sf::Vector2f& position)
{
	characterSprite.setPosition(position);
}
