#include "Dog.h"

Dog::Dog() : Character(CharacterData("dog", 192, 48, 48, 0, 48, 150.f))
{
	characterSprite.setPosition({ 1000.f, 720.f / 2.f });
	characterSprite.scale({ 2.f, 2.f });
	characterSprite.addAnimation("idle");
}