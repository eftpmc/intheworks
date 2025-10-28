#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.h"

class Game {
	public:
		Game();
		void run();
	private:
		sf::RenderWindow window;
		Player player;

		void processEvents();
		void update(sf::Time deltaTime);
		void render();
};