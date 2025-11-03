#include "Soldier.h"

Soldier::Soldier() : Character(CharacterData("soldier", 600, 100, 100, 0, 100, 30.f))
{
	characterSprite.setPosition({ 1000.f, 720.f / 2.f });
	characterSprite.scale({ 1.5f, 1.5f });
	characterSprite.addAnimation("idle");
	characterSprite.addAnimation("walk");
}