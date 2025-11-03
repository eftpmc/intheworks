#include "Orc.h"

Orc::Orc() : Character(CharacterData("orc", 600, 100, 100, 0, 100, 20.f))
{
	characterSprite.setPosition({ 200.f, 720.f / 2.f });
	characterSprite.scale({ 1.5f, 1.5f });
	characterSprite.addAnimation("idle");
	characterSprite.addAnimation("walk");
}