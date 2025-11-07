#pragma once
#include <string>
#include <SFML/System.hpp>
#include <iostream>
#include "DataClasses.h"

class Character;

class GameObject;

struct ActionContext {
	Character* actor = nullptr;
	GameObject* target = nullptr;
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

class ChoppingAction : public Action {
public:
	ChoppingAction()
		: Action("Chop Wood", CharacterData(0.f)) {}
	void start() override;
	void update(sf::Time dt) override;
	void completeAction() override;
private:
	bool harvested = false;
};

class MoveToAction : public Action {
	public:
	MoveToAction()
		: Action("Move To Target", CharacterData(0.f)) {}
	void start();
	void update(sf::Time dt);
	void completeAction() override;
};