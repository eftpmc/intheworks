#include "Game.h"

Game::Game()
	: window(sf::VideoMode({ 1280, 720 }), "SFML Game"){ 
	
}

void Game::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
	}
}

void Game::update(sf::Time deltaTime)
{
	player.handleInput();
	player.update(deltaTime);
	dog.update(deltaTime);
}

void Game::render()
{
	window.clear(sf::Color::White);

	player.draw(window);
	dog.draw(window);

	window.display();
}