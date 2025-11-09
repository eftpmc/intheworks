#include "Map.h"
#include "Clan.h"

Map::Map() : rectSourceSprite(sf::Vector2(0,0), sf::Vector2(16,16)), infile("map.csv") {
	clan = new Clan(this);

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

	characterManager.createCharacter("Base", sf::Vector2f(800, 500));
	objectManager.createObject("Tree", sf::Vector2f(1000.f, 100.f));
	objectManager.createObject("Tree", sf::Vector2f(1100.f, 300.f));
	objectManager.createObject("Tree", sf::Vector2f(900.f, 700.f));

	Character* human = characterManager.queryArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f))[0];
	clan->addMember(human);
}

void Map::update(sf::Time& deltaTime) {
	characterManager.update(deltaTime);
	objectManager.update(deltaTime);
}

void Map::draw(sf::RenderWindow& window) const {
	for (const auto& tile : mapTiles) {
		window.draw(tile);
	}
	characterManager.draw(window);
	objectManager.draw(window);
}