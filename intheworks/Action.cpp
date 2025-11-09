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

	if (ctx.target->isActive) {

		if (elapsedTime.asSeconds() >= .6f && stage == 1) {
			if (auto* resource = dynamic_cast<ResourceObject*>(ctx.target)) {
				resource->harvest(5);

				elapsedTime = sf::Time::Zero;
				stage++;
			}
		}
		else if (elapsedTime.asSeconds() >= .2f && stage == 2) {
			elapsedTime = sf::Time::Zero;
			stage = 1;
		}
	}
	else {
		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < 3; i++) {
			int min = 0;
			int max = 20;
			int x = (min + (rand() % (max - min + 1))) - 10;
			int y = (min + (rand() % (max - min + 1))) - 10;
			ctx.map->getObjectManager().createObject("Wood", sf::Vector2f(ctx.target->position.x + x, ctx.target->position.y + y));
		}
		ctx.actor->actionCompleted(std::make_unique<ChoppingAction>());
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

void PickUpAction::start() {
	ctx.actor->addToInventory(ctx.target->getType(), 5);
	ctx.actor->actionCompleted(std::make_unique<PickUpAction>());
}

void PickUpAction::update(sf::Time dt) {
	
}

void PickUpAction::completeAction() {
	ctx.map->getObjectManager().removeObject(ctx.target);
}