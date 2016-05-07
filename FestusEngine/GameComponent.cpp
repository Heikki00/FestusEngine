#include "GameComponent.h"
#include "GameObject.h"
#include "CoreEngine.h"

U32 GameComponent::IDCounter = 0;



GameObject* GameComponent::getParent() const
{
	return parent;
}

Transform& GameComponent::getTransform()
{
	
	return parent->getTransform();

}

U32 GameComponent::getType() const
{
	return type;
}



void GameComponent::setParent(GameObject* parent) {
	this->parent = parent;
}
