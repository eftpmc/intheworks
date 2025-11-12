#include "Selector.h"
#include "../Map.h"
#include "Sequence.h"


Selector::Selector() {

}

void Selector::sequenceCompleted(Sequence* sequence) {
	if (sequence == currentSequence) {
		currentSequence = nullptr;
	}
}

bool Selector::getCondition() {
	bool pass = false;
	for (auto& condition : conditions) {
		ConditionContext conditionContext{ this, ctx.map };
		pass = condition->check(conditionContext);
	}

	return pass;
}

void Selector::setContext(const SelectorContext& context) {
	{ ctx = context; }
}
SelectorContext& Selector::getContext() {
	return ctx;
}

shouldChopWoodSelector::shouldChopWoodSelector() {
	conditions.push_back(std::make_unique<isTreeAvailableCondition>());
}
void shouldChopWoodSelector::update(sf::Time deltaTime) {
	if (!currentSequence) {
		if (getCondition()) {
			SequenceContext sequenceContext{ this, ctx.actor, ctx.map };
			currentSequence = new ChopWoodSequence();
			currentSequence->setContext(sequenceContext);
			currentSequence->start();
		}
		else {
			std::cout << "nofing to do" << std::endl;
		}
	}
	else {
		currentSequence->update(deltaTime);
	}
}