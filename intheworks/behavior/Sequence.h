#pragma once
#include <memory>
#include <queue>
#include <SFML/System.hpp>

class Selector;
class Character;
class Map;
class Action;
class MoveToClosestTreeAction;
class ChopTreeAction;

struct SequenceContext {
	Selector* selector = nullptr;
	Character* actor = nullptr;
	Map* map = nullptr;
};

class Sequence {
public:
	Sequence();
	void start();
	void update(sf::Time deltaTime);
	void setContext(const SequenceContext& context);
	SequenceContext& getContext();
	void actionCompleted(std::unique_ptr<Action> action);
protected:
	std::queue<std::unique_ptr<Action>> schedule;
	SequenceContext ctx;
};

class ChopWoodSequence : public Sequence {
public:
	ChopWoodSequence();
};