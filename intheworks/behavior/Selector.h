#pragma once
#include "../Map.h"
#include "Sequence.h"
#include "Condition.h"

struct SelectorContext {
	Character* actor = nullptr;
	Map* map = nullptr;
};

class Selector {
public:
	Selector();
	virtual void update(sf::Time deltaTime) = 0;
	void sequenceCompleted(Sequence* sequence);
	bool getCondition();
	void setContext(const SelectorContext& context);
	SelectorContext& getContext();
protected:
	SelectorContext ctx;
	Sequence* currentSequence = nullptr;
	std::vector<std::unique_ptr<Condition>> conditions;
};

class shouldChopWoodSelector : public Selector {
public:
	shouldChopWoodSelector();
	void update(sf::Time deltaTime) override;
};