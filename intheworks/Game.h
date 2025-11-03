#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Map.h"


class Game {
	public:
		Game();
		void run();
	private:
		sf::RenderWindow window;
		sf::View view;

		Map map;
		bool dragging = false;
		sf::Vector2f oldPos;
		float zoom = 1;

		void processEvents();
		void update(sf::Time deltaTime);
		void render();
};