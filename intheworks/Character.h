#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include "AnimatedSprite.h"
#include "DataClasses.h"
#include "Action.h"

class Character;
class Map;

class CharacterState {
public:
    virtual ~CharacterState() = default;
    virtual void onEnter(Character& character) {}
    virtual void onExit(Character& character) {}
    virtual void update(Character& character, sf::Time dt) = 0;
};

class Idle : public CharacterState {
    public:
    void onEnter(Character& character) override;
	void update(Character& character, sf::Time dt) override;
};

class Moving : public CharacterState {
public:
    void onEnter(Character& character) override;
    void update(Character& character, sf::Time dt) override;
};

class Character {
public:
    Character(const CharacterData& charData, const AnimatedSpriteData& spriteData);
    virtual void update(sf::Time deltaTime, Map& map);
    void draw(sf::RenderWindow& window) const;

    const CharacterData getCharacterData();
    sf::Vector2f getDirection() const;
    sf::Vector2f getPosition() const;

    void setState(std::unique_ptr<CharacterState> newState);
    void setAnimation(const std::string& animationName);
	void setDirection(const sf::Vector2f& dir);
    void setPosition(const sf::Vector2f& position);

	bool requestAction(std::unique_ptr<Action> action);
	void actionCompleted(std::unique_ptr<Action> action);

	bool moveTo(const GameObject* target);
    void move(const sf::Vector2f& offset);
	void scale(const sf::Vector2f& factors);
protected:
    AnimatedSprite characterSprite;
	const CharacterData characterData;

    std::unique_ptr<CharacterState> currentState;
	std::queue<std::unique_ptr<Action>> schedule;

    sf::Vector2f direction;
};
