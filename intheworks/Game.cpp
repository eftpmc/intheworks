#include "Game.h"

Game::Game()
	: window(sf::VideoMode({ 1280, 720 }), "SFML Game") {
	view = window.getDefaultView();
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

		if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			dragging = true;
			oldPos = window.mapPixelToCoords(sf::Vector2i(mouseButtonPressed->position.x, mouseButtonPressed->position.y));
		}

		if (event->is<sf::Event::MouseButtonReleased>())
		{
			dragging = false;
		}

		if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
		{
			if (!dragging)
				break;

			const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));

			const sf::Vector2f deltaPos = oldPos - newPos;

			view.setCenter(view.getCenter() + deltaPos);
			window.setView(view);

			oldPos = window.mapPixelToCoords(sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));
			break;
		}

		if (const auto* mouseWheelScroll = event->getIf<sf::Event::MouseWheelScrolled>()) {
			if (dragging)
				break;

			if (mouseWheelScroll->delta <= -1)
				zoom = std::min(2.f, zoom + .1f);
			else if (mouseWheelScroll->delta >= 1)
				zoom = std::max(.5f, zoom - .1f);

			// Update our view
			view.setSize(window.getDefaultView().getSize());
			view.zoom(zoom);
			window.setView(view);
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	map.update(deltaTime);
}

void Game::render()
{
	window.clear(sf::Color::Black);

	map.draw(window);

	window.display();
}