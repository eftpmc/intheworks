#include "Condition.h"
#include "../Map.h"
#include "Selector.h"

Condition::Condition() {

}

isTreeAvailableCondition::isTreeAvailableCondition() {

}

bool isTreeAvailableCondition::check(ConditionContext& ctx) {
	auto list = ctx.map->getObjectManager().queryArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f));
	return !list.empty();
}