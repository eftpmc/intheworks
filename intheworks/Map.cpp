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
		AnimatedSpriteData("base", 768, 64, Size(64, 64), Size(16,0), 96, .1f)
		));
	objectManager.createObject("Tree", sf::Vector2f(1000.f, 100.f));
	objectManager.createObject("Tree", sf::Vector2f(1100.f, 300.f));
	objectManager.createObject("Tree", sf::Vector2f(900.f, 700.f));


	std::vector<GameObject*> assigned;

	for (int i = 0; i < 3; i++) {
		std::vector<GameObject*> query = objectManager.queryArea(
			sf::Vector2f(0.f, 0.f),
			sf::Vector2f(1280.f, 720.f),
			"Tree"
		);

		auto it = std::find_if(query.begin(), query.end(),
			[&assigned](GameObject* obj) {
				bool alreadyAssigned = std::find(assigned.begin(), assigned.end(), obj) != assigned.end();
				return obj && obj->isActive && !alreadyAssigned;
			});

		if (it != query.end()) {
			GameObject* target = *it;
			characters[0]->requestAction(std::make_unique<MoveToAction>(), target, this);
			characters[0]->requestAction(std::make_unique<ChoppingAction>(), target, this);
			assigned.push_back(target);
		}
	}
}

void Map::update(sf::Time& deltaTime) {
	for (auto& character : characters) {
		character->update(deltaTime, *this);
	}
	objectManager.update(deltaTime);
}

void Map::draw(sf::RenderWindow& window) const {
	for (const auto& tile : mapTiles) {
		window.draw(tile);
	}
	for (const auto& character : characters) {
		character->draw(window);
	}
	objectManager.draw(window);
}