#include "Clan.h"

Clan::Clan(Map* map): map(map) {
}

void Clan::update(sf::Time deltaTime) {

}

void Clan::addMember(Character* character) {
	members.push_back(character);
}

void Clan::chopTree() {
	std::vector<GameObject*> treeQuery = map->getObjectManager().queryArea(
		sf::Vector2f(0.f, 0.f),
		sf::Vector2f(1280.f, 720.f),
		"Tree"
	);

	auto it = std::find_if(treeQuery.begin(), treeQuery.end(),
		[this](GameObject* obj) {
			bool alreadyAssigned = std::find(assigned.begin(), assigned.end(), obj) != assigned.end();
			return obj && obj->isActive && !alreadyAssigned;
		});

		if (it != treeQuery.end()) {
			GameObject* target = *it;
			members[0]->requestAction(std::make_unique<MoveToAction>(), target, map);
			members[0]->requestAction(std::make_unique<ChoppingAction>(), target, map);

			assigned.push_back(target);
		}
}