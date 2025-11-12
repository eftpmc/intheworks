#pragma once
#include <SFML/System.hpp>
#include <vector>

class Selector;
class Map;

struct ConditionContext {
	Selector* selector;
	Map* map = nullptr;
};


class Condition {
public:
	Condition();

	virtual bool check(ConditionContext& ctx) = 0;
};

class isTreeAvailableCondition : public Condition {
public:
	isTreeAvailableCondition();
	bool check(ConditionContext& ctx) override;
};