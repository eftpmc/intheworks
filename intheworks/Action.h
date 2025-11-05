#pragma once
#include <string>
#include <SFML/System.hpp>
#include <iostream>
#include "DataClasses.h"

class Character;

class GameObject;

struct ActionContext {
	Character* actor;
	GameObject* target;
};

class Action {
public:
	Action(const std::string& name, const CharacterData& minConditions)
		: name(name), minConditions(minConditions) {
	}
	virtual void start(ActionContext& ctx) = 0;
	virtual void update(ActionContext& ctx, sf::Time dt) = 0;
	virtual bool isComplete(ActionContext& ctx) const = 0;

	std::string getName() const { return name; }
	const CharacterData& getMinConditions() const { return minConditions; }
protected:
	std::string name;
	const CharacterData minConditions;
	sf::Time elapsedTime;
};

class ChoppingAction : public Action {
public:
	ChoppingAction()
		: Action("Chop Wood", CharacterData(0.f)) {}
	void start(ActionContext& ctx) override;
	void update(ActionContext& ctx, sf::Time dt) override;
	bool isComplete(ActionContext& ctx) const override {
		// Check if chopping is complete
		return false;
	}
};