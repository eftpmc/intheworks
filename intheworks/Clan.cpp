#include "Clan.h"

Clan::Clan() {
	members.push_back(Character(CharacterData("orc", 600, 100, 100, 0, 100, 20.f)));
}

void Clan::update(sf::Time deltaTime) {
	for (auto& member : members) {
		member.update(deltaTime);
	}
}

void Clan::draw(sf::RenderWindow& window) const {
	for (const auto& member : members) {
		member.draw(window);
	}
}