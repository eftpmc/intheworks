#include "Action.h"
#include "../Character.h"
#include "../GameObject.h"
#include "../Map.h"
#include "Sequence.h"

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
void ChopTreeAction::start(){
	std::vector<GameObject*> list = ctx.map->getObjectManager().queryArea(ctx.actor->getPosition(), sf::Vector2f(50, 50));
	if (!list.empty()) {
		tree = list[0];
	}
	else {
		ctx.sequence->actionCompleted(std::make_unique<ChopTreeAction>());
	}

	ctx.actor->setState(std::make_unique<Chopping>() );
}

void ChopTreeAction::update(sf::Time dt) {
	elapsedTime += dt;

	if (tree->isActive && tree) {

		if (elapsedTime.asSeconds() >= .6f && stage == 1) {
			if (auto* resource = dynamic_cast<ResourceObject*>(tree)) {
				resource->harvest(5);
				ctx.actor->addToInventory(tree->getType(), 5);

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
		ctx.sequence->actionCompleted(std::make_unique<ChopTreeAction>());
	}
}

void ChopTreeAction::completeAction() {
	ctx.actor->setState(std::make_unique<Idle>());
	tree->setTexture("cut");
	std::cout << "Chopping action complete." << std::endl;
}

void MoveToClosestTreeAction::start() {
	std::vector<GameObject*> list = ctx.map->getObjectManager().queryArea(sf::Vector2f(0.f,0.f), sf::Vector2f(1280.f, 720.f));
	if (!list.empty()) {
		std::cout << "not empty" << std::endl;
		tree = list[0];
	}
	else {
		ctx.sequence->actionCompleted(std::make_unique<MoveToClosestTreeAction>());
	}

	ctx.actor->setState(std::make_unique<Moving>());
}

void MoveToClosestTreeAction::update(sf::Time dt) {
	bool arrived = ctx.actor->moveTo(tree);

	if (arrived) {
		ctx.sequence->actionCompleted(std::make_unique<MoveToClosestTreeAction>());
	}
}

void MoveToClosestTreeAction::completeAction() {
	ctx.actor->setState(std::make_unique<Idle>());
	std::cout << "MoveTo action complete." << std::endl;
}