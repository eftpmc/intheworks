#include "Map.h"

Map::Map() : rectSourceSprite(sf::Vector2(0,0), sf::Vector2(16,16)), infile("map.csv") {
	if (!texture.loadFromFile("tileset.png", false))
	{
		// error...
	}

	int lineNumber = 0;
	std::string line;
	while (std::getline(infile, line)) {
		std::stringstream s(line);

		int columnNumber = 0;
		while( s.good()) {
			std::string substr;
			std::getline( s, substr, ',' );
			
			sf::Sprite tileSprite(texture);
			int x = (stoi(substr) % 64) * 16;
			int y = (stoi(substr) / 64) * 16;
			rectSourceSprite.position.x = x;
			rectSourceSprite.position.y = y;
			tileSprite.setTextureRect(rectSourceSprite);
			tileSprite.setPosition({ 16.f * columnNumber, 16.f * lineNumber});

			mapTiles.push_back(tileSprite);
			columnNumber++;
		}
		lineNumber++;
	}
}

void Map::update(sf::Time& deltaTime) {
	orc.update(deltaTime);
}

void Map::draw(sf::RenderWindow& window) const {
	for (const auto& tile : mapTiles) {
		window.draw(tile);
	}
	orc.draw(window);
}