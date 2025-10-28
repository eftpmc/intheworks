#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Character.h"

class Player : public Character {
	public:
		Player();
		void handleInput();
};