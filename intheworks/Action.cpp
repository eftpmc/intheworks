#include "Action.h"
#include "Character.h"
#include "GameObject.h"
#include "Map.h"

void Action::setContext(const ActionContext& context) {
	{ ctx = context; }
}

ActionContext& Action::getContext() {
	return ctx;
}

std::string Action::getName() const {
	return name;
}

const CharacterData& Action::getMinConditions() const {
	return minConditions;
}
void ChoppingAction::start(){
	ctx.actor->setState(std::make_unique<Chopping>() );
}

void ChoppingAction::update(sf::Time dt) {
    elapsedTime += dt;

    if (!ctx.target->isActive) {
        // Once inactive, finalize the chop
        ctx.target->setTexture("cut");
        ctx.actor->actionCompleted(std::make_unique<ChoppingAction>());
        return;
    }

    // Axe impact around 0.7s -> trigger shake + harvest
    if (elapsedTime.asSeconds() >= 0.7f && stage == 1) {
        ctx.target->setTexture("shake");

        if (auto* resource = dynamic_cast<ResourceObject*>(ctx.target)) {
            resource->harvest(5);
            ctx.actor->addToInventory(resource->resourceType, 5);

            // Optional: if resource depleted, it will become inactive,
            // triggering the above 'inactive' branch next update
        }

        stage++;
        elapsedTime = sf::Time::Zero;
    }

    // Allow shake to play for full duration (~0.2s total)
    if (elapsedTime.asSeconds() >= 0.2f && stage == 2) {
        ctx.target->setTexture("idle");
        stage = 1;                 // ready for next swing if looping
        elapsedTime = sf::Time::Zero;
    }
}

void ChoppingAction::completeAction() {
	ctx.actor->setState(std::make_unique<Idle>());
	ctx.target->setTexture("cut");
	std::cout << "Chopping action complete." << std::endl;
}

void MoveToAction::start() {
	ctx.actor->setState(std::make_unique<Moving>());
}

void MoveToAction::update(sf::Time dt) {
	bool arrived = ctx.actor->moveTo(ctx.target);

	if (arrived) {
		ctx.actor->actionCompleted(std::make_unique<MoveToAction>());
	}
}

void MoveToAction::completeAction() {
	ctx.actor->setState(std::make_unique<Idle>());
	std::cout << "MoveTo action complete." << std::endl;
}