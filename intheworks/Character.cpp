#include "Character.h"
#include "Map.h"

Character::Character(const CharacterData& charData, const AnimatedSpriteData& spriteData)
	: characterData(charData), characterSprite(spriteData)
{
	direction = { 0.f, 0.f };
	
	characterSprite.addTexture("idle", 0);
	characterSprite.addTexture("idle", 1);
	characterSprite.addTexture("idle", 2);

	characterSprite.addTexture("walk", 0);
	characterSprite.addTexture("walk", 1);
	characterSprite.addTexture("walk", 2);

	characterSprite.addTexture("attack", 0);
	characterSprite.addTexture("attack", 1);
	characterSprite.addTexture("attack", 2);

	characterSprite.addTexture("axe", 0);
	characterSprite.addTexture("axe", 1);
	characterSprite.addTexture("axe", 2);

	characterSprite.setPosition({ 1000.f, 720.f / 2.f });

	setState(std::make_unique<Idle>());
}

void Idle::onEnter(Character& character)
{
	character.setAnimation("idle");
	character.setDirection({ 0.f, 0.f });
}

void Idle::update(Character& character, sf::Time dt)
{
}

void Moving::onEnter(Character& character)
{
	character.setAnimation("walk");
}

void Moving::update(Character& character, sf::Time dt)
{
	sf::Vector2f offset = character.getDirection() * character.getCharacterData().moveSpeed * dt.asSeconds();
	character.move(offset);

	if (offset.x > 0) {
		character.scale({ 1.f, 1.f });
	}
	else
	{
		character.scale({ -1.f, 1.f });
	}
}

void Attacking::onEnter(Character& character)
{
	character.setAnimation("attack");
}

void Attacking::update(Character& character, sf::Time dt)
{
}

void Chopping::onEnter(Character& character)
{
	character.setAnimation("axe");
}

void Chopping::update(Character& character, sf::Time dt)
{
}

void Character::update(sf::Time deltaTime, Map& map)
{
	characterSprite.update(deltaTime);
	if(currentState)
		currentState->update(*this, deltaTime);

	if (!schedule.empty())
	{
		schedule.front()->update(deltaTime);
	}
}

void Character::draw(sf::RenderWindow& window) const
{
	characterSprite.draw(window);
}

const CharacterData Character::getCharacterData()
{
	return characterData;
}

sf::Vector2f Character::getPosition() const
{
	return characterSprite.getPosition();
}

sf::Vector2f Character::getDirection() const
{
	return direction;
}

void Character::setState(std::unique_ptr<CharacterState> newState)
{
	if (currentState)
		currentState->onExit(*this);

	currentState = std::move(newState);

	if (currentState)
		currentState->onEnter(*this);
}

void Character::setAnimation(const std::string& animationName)
{
	characterSprite.setTexture(animationName);
}

void Character::setDirection(const sf::Vector2f& dir)
{
	direction = dir;
}

void Character::setPosition(const sf::Vector2f& position)
{
	characterSprite.setPosition(position);
}

bool Character::moveTo(const GameObject* target)
{
	sf::Vector2f charPos = getPosition();
	sf::Vector2f targetPos = target->position;

	sf::Vector2f directionToTarget = targetPos - charPos;
	float length = std::sqrt(directionToTarget.x * directionToTarget.x + directionToTarget.y * directionToTarget.y);

	if (length > 0.f) {
		directionToTarget /= length;
	}

	setDirection(directionToTarget);

	float distance = pow(pow((targetPos.x - charPos.x), 2) + pow((targetPos.y - charPos.y), 2), 0.5);
	if (distance < 20.f) {
		return true;
	}

	return false;
}

void Character::move(const sf::Vector2f& offset)
{
	characterSprite.move(offset);
}

void Character::scale(const sf::Vector2f& factors)
{
	characterSprite.scale(factors);
}

bool Character::requestAction(std::unique_ptr<Action> action, GameObject* target, Map* map)
{
	for(int i = 0; i < sizeof(CharacterData) / sizeof(float); i++)
	{
		const float* characterDataPtr = reinterpret_cast<const float*>(&characterData);
		const float* minConditionsPtr = reinterpret_cast<const float*>(&action->getMinConditions());
		if (characterDataPtr[i] < minConditionsPtr[i])
			return false;
	}

	ActionContext ctx{ this, target, map };
	action->setContext(ctx);

	schedule.push(std::move(action));

	if(schedule.size() == 1)
	{
		schedule.front()->start();
	}
	return true;
}

void Character::actionCompleted(std::unique_ptr<Action> action)
{
	if (!schedule.empty() && schedule.front()->getName() == action->getName())
	{
		schedule.front()->completeAction();
		schedule.pop();
	}

	if (!schedule.empty())
	{
		schedule.front()->start();
	}
}