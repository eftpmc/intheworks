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

	characters.push_back(std::make_unique<Character>(
		CharacterData(50.f),
		AnimatedSpriteData("orc", 600, 100, Size(100, 100), 0, 100, .1f)
		));
	objects.push_back(std::make_unique<Tree>(
		AnimatedSpriteData("tree", 112, 42, Size(28, 42), 0, 28, .5f),
		sf::Vector2f(800.f, 400.f),
		"Wood",
		50
	));


	characters[0]->requestAction(std::make_unique<MoveToAction>(), objects[0].get());
	characters[0]->requestAction(std::make_unique<ChoppingAction>(), objects[0].get());
}

void Map::update(sf::Time& deltaTime) {
	for (auto& character : characters) {
		character->update(deltaTime, *this);
	}
	for (auto& object : objects) {
		object->update(deltaTime);
	}
}

void Map::draw(sf::RenderWindow& window) const {
	for (const auto& tile : mapTiles) {
		window.draw(tile);
	}
	for (const auto& character : characters) {
		character->draw(window);
	}
	for (const auto& object : objects) {
		object->draw(window);
	}
}