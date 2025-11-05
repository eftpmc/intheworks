#include "Action.h"
#include "Character.h"
#include "GameObject.h"

void ChoppingAction::start(ActionContext& ctx){
	ctx.actor->setState(std::make_unique<Idle>() );
}

void ChoppingAction::update(ActionContext& ctx, sf::Time dt) {
	elapsedTime += dt;

	if (ctx.target->isActive) {
			ctx.actor->setAnimation("attack");

			if (elapsedTime.asSeconds() >= 2.f) {
				if (auto* resource = dynamic_cast<ResourceObject*>(ctx.target)) {
					resource->harvest(5);

					elapsedTime = sf::Time::Zero;
				}
			}
	}
	else {
		ctx.actor->setState(std::make_unique<Idle>());
		ctx.target->setTexture("cut");
		ctx.actor->actionCompleted(std::make_unique<ChoppingAction>());
		std::cout << "Chopping action complete." << std::endl;
	}
}

void MoveToAction::start(ActionContext& ctx) {
	ctx.actor->setState(std::make_unique<Moving>());
}

void MoveToAction::update(ActionContext& ctx, sf::Time dt) {
	bool arrived = ctx.actor->moveTo(ctx.target);

	if (arrived) {
		ctx.actor->setState(std::make_unique<Idle>());
		ctx.actor->actionCompleted(std::make_unique<MoveToAction>());
		std::cout << "MoveTo action complete." << std::endl;
	}
}