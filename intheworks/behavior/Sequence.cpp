#include "Sequence.h"
#include "Selector.h"
#include "Action.h"

Sequence::Sequence() {

}

void Sequence::start() {
	if (!schedule.empty()) {
		ActionContext actionContext{ this, ctx.actor, ctx.map };
		schedule.front()->setContext(actionContext);

		schedule.front()->start();
	}
}

void Sequence::update(sf::Time deltaTime) {
	if (!schedule.empty())
	{
		schedule.front()->update(deltaTime);
	}
	else {
		ctx.selector->sequenceCompleted(this);
	}
}

void Sequence::setContext(const SequenceContext& context) {
	{ ctx = context; }
}

SequenceContext& Sequence::getContext() {
	return ctx;
}

void Sequence::actionCompleted(std::unique_ptr<Action> action) {
	if (!schedule.empty() && schedule.front()->getName() == action->getName())
	{
		schedule.front()->completeAction();
		schedule.pop();
	}

	if (!schedule.empty())
	{
		ActionContext actionContext{ this, ctx.actor, ctx.map };
		schedule.front()->setContext(actionContext);
		schedule.front()->start();
	}
}

ChopWoodSequence::ChopWoodSequence() {
	schedule.push(std::make_unique<MoveToClosestTreeAction>());
	schedule.push(std::make_unique<ChopTreeAction>());
}