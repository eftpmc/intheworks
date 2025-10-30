#include "Player.h"

Player::Player() : Character(CharacterData("hero", 1280, 128, 32, 48, 128, 175.f))
{
    characterSprite.setPosition({ 1280.f / 2.f, 720.f / 2.f });
	characterSprite.scale({ 3.f, 3.f });

	characterSprite.addAnimation("idle");
	characterSprite.addAnimation("walk");
    characterSprite.addAnimation("sprint");
}

void Player::handleInput()
{
    velocity = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        velocity.x -= 1.f;
		if(facing != -1){
            characterSprite.scale({ -1.f, 1.f });
            facing = -1;
        }
    }
        
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        velocity.x += 1.f;
        if (facing != 1) {
            characterSprite.scale({ -1.f, 1.f });
            facing = 1;
        }
    }
}
