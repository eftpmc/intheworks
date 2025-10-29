#include "Character.h"

Character::Character(const CharacterData& data) 
	: characterSprite(data), speed(data.moveSpeed)
{
}

void Character::update(sf::Time deltaTime)
{
	if (velocity.x > 0.f || velocity.x < 0.f || velocity.y > 0.f || velocity.y < 0.f) {
		state = 2;
		characterSprite.move(velocity * speed * deltaTime.asSeconds());
	}
	else {
		state = 1;
	}

	characterSprite.update(deltaTime, state);
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