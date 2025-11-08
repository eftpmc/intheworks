#include "CharacterManager.h"

CharacterManager::CharacterManager() {
    defaultCharacters.emplace("Base",
        std::make_unique<Character>(
            CharacterData(50.f),
            AnimatedSpriteData("base", 768, 64, Size(64, 64), Size(16, 0), 96, .1f)
        )
    );
}
void CharacterManager::update(sf::Time deltaTime) {
    for (const auto& pair : characters) {
        for (const auto& character : pair.second) {
            character.get()->update(deltaTime);
        }
    }
}

void CharacterManager::draw(sf::RenderWindow& window) const {
    for (const auto& pair : characters) {
        for (const auto& character : pair.second) {
            character.get()->draw(window);
        }
    }
}

std::vector<Character*> CharacterManager::getCharacters() {
    std::vector<Character*> results;

    for (const auto& pair : characters) {
        for (const auto& character : pair.second) {
            results.push_back(character.get());
        }
    }

    return results;
}

void CharacterManager::createCharacter(std::string characterName, sf::Vector2f pos) {
    if (defaultCharacters.find(characterName) != defaultCharacters.end()) {
        characters[characterName].push_back(defaultCharacters[characterName]->clone());
        characters[characterName].back().get()->setPosition(pos);
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

std::vector<Character*> CharacterManager::queryArea(const sf::Vector2f& pos,
    const sf::Vector2f& size) {
    std::vector<Character*> results;

    for (const auto& [name, list] : characters) {
        for (const auto& character : list) {
            if (!character) continue;

            const sf::Vector2f& objPos = character->getPosition();
            const sf::Vector2f& objSize = sf::Vector2f(16,16);

            if (aabbOverlap(pos, size, objPos, objSize)) {
                results.push_back(character.get());
            }
        }
    }

    return results;
}
