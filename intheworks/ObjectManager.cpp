#include "ObjectManager.h"
#include "Tree.h"
#include "Wood.h"

ObjectManager::ObjectManager() {
	defaultObjects.emplace(
		"Tree",
		std::make_unique<Tree>(
			AnimatedSpriteData("tree", 112, 42, Size(28, 42), Size(0, 0), 28, .05f),
			"Wood",
			50));

    defaultObjects.emplace(
        "Wood",
        std::make_unique<Wood>(
            AnimatedSpriteData("wood", 16, 16, Size(16, 16), Size(0, 0), 16, .5f)));
}
void ObjectManager::update(sf::Time deltaTime) {
    for (const auto& pair : objects) {
        for (const auto& object : pair.second) {
            object.get()->update(deltaTime);
        }
    }
}
void ObjectManager::draw(sf::RenderWindow& window) const {
	for (const auto& pair : objects) {
		for (const auto& object : pair.second) {
			object.get()->draw(window);
		}
	}
}
void ObjectManager::createObject(std::string objectName, sf::Vector2f pos) {
	if (defaultObjects.find(objectName) != defaultObjects.end()) {
		objects[objectName].push_back(defaultObjects[objectName]->clone());
		objects[objectName].back().get()->setPosition(pos);
	}
}

namespace {
    inline bool aabbOverlap(const sf::Vector2f& posA, const sf::Vector2f& sizeA,
        const sf::Vector2f& posB, const sf::Vector2f& sizeB) {
        return (posA.x < posB.x + sizeB.x) &&
            (posA.x + sizeA.x > posB.x) &&
            (posA.y < posB.y + sizeB.y) &&
            (posA.y + sizeA.y > posB.y);
    }
}

std::vector<GameObject*> ObjectManager::queryArea(const sf::Vector2f& pos,
    const sf::Vector2f& size,
    const std::string& type) {
    std::vector<GameObject*> results;

    for (const auto& [name, list] : objects) {
        for (const auto& object : list) {
            if (!object || !object->isActive) continue;

            const sf::Vector2f& objPos = object->position;
            const sf::Vector2f& objSize = object->bounds.size;

            if (!type.empty() && object->getType() != type) continue;

            if (aabbOverlap(pos, size, objPos, objSize)) {
                results.push_back(object.get());
            }
        }
    }

    return results;
}
