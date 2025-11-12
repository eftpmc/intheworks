#pragma once
#include <string>
#include <SFML/System.hpp>
#include <iostream>
#include "../DataClasses.h"

class Character;

class GameObject;

class Map;

class Sequence;

struct ActionContext {
	Sequence* sequence = nullptr;
	Character* actor = nullptr;
	Map* map = nullptr;
};

class Action {
public:
	Action(const std::string& name, const CharacterData& minConditions)
		: name(name), minConditions(minConditions) {
	}

	void setContext(const ActionContext& context);
	ActionContext& getContext();

	virtual void start() = 0;
	virtual void update( sf::Time dt) = 0;
	virtual void completeAction() = 0;

	std::string getName() const;
	const CharacterData& getMinConditions() const;
protected:
	std::string name;
	const CharacterData minConditions;
	sf::Time elapsedTime;
	ActionContext ctx;
};

class ChopTreeAction : public Action {
public:
	ChopTreeAction()
		: Action("Chop Wood", CharacterData(0.f)) {}
	void start() override;
	void update(sf::Time dt) override;
	void completeAction() override;
private:
	int stage = 1;
	GameObject* tree = nullptr;
};

class MoveToClosestTreeAction : public Action {
	public:
		MoveToClosestTreeAction()
		: Action("Move To Closest Tree", CharacterData(0.f)) {}
	void start();
	void update(sf::Time dt);
	void completeAction() override;
private:
	GameObject* tree = nullptr;
};