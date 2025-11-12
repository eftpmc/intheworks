#include "Clan.h"

Clan::Clan(Map* map): map(map) {
}

void Clan::update(sf::Time deltaTime) {

}

void Clan::addMember(Character* character) {
	members.push_back(character);
}