
#include "GameObject.h"
#include "CoreEngine.h"
#include "GameComponent.h"
#include "boost/algorithm/string/join.hpp"



GameObject::GameObject(const std::string& name) : ID(++IDCounter)
{
	transform = new Transform;
	this->name = name;
	parent = nullptr;
}

GameObject::~GameObject()
{
	for (GameComponent* c : components) {
		c->free();
		delete c;
	};

	for (GameObject* g : children) delete g;

	delete transform;
}




void GameObject::addChild(GameObject* child)
{
	child->getTransform().setParent(this->transform);
	child->parent = this;
	children.push_back(child);

}


void GameObject::addComponent(GameComponent* component)
{
	component->setParent(this);
	component->init();
	components.push_back(component);
}





void GameObject::render(U32 renderType)
{
	for (GameComponent* c : components) c->render(renderType);
}


void GameObject::update()
{
	for (GameComponent* c : components) c->update();
}

void GameObject::renderAll(U32 renderType)
{
	render(renderType);
	for (GameObject* child : children) child->renderAll(renderType);
}

void GameObject::updateAll()
{
	update();
	for (GameObject* child : children) child->updateAll();
}




ObjectSaveData GameObject::save()
{
	ObjectSaveData res;
	res.name = &name;
	res.transform = transform;
	res.componentData.reserve(components.size());
	res.childSaveData.reserve(children.size());

	for (GameComponent* c : components) {
		res.componentData.push_back(c->save());
	}
	
	for (GameObject* child : children) {
		res.childSaveData.push_back(child->save());
	}

	return res;

}

U32 GameObject::getNumChildren() const
{
	return children.size();
}

std::vector<GameObject*> GameObject::getChildren()
{
	return children;
}

GameObject* GameObject::getChildByIndex(U32 index){

	return index < children.size() ? children.at(index) : nullptr;
}

GameObject* GameObject::getChildByName(const string& name)
{

	for (GameObject* child : children) {
		if (child->name == name) return child;
	}
	return nullptr;


}

bool GameObject::isChild(const GameObject* g) const
{
	return g->parent == this;

}




U32 GameObject::getNumAttached() const
{
	U32 sum = children.size();

	for (GameObject* g : children) sum += g->getNumAttached();

	return sum;
}


//TODO: is this the best way to do this?
std::vector<GameObject*> GameObject::getAllAttached()
{
	std::vector<GameObject*> vec = children;
	for (GameObject* g : children) {
		auto cVec = g->getAllAttached();
		vec.reserve(vec.size()+ cVec.size());
		vec.insert(vec.end(), cVec.begin(), cVec.end());

	}
	return vec;
}

//Or this?
GameObject* GameObject::getAttachedByID(U32 ID)
{
	for (GameObject* g : getAllAttached()) if (g->ID == ID) return g;
	return nullptr;
}

bool GameObject::isAttached(const GameObject* g) const
{
	const GameObject* gg = g;
	while (true) {
		if (gg->parent == this) {
			return true;
		}
	
		gg = gg->parent;
		if (!gg) {
			break;
		}

	}
	return false;
}

U32 GameObject::getNumComponents() const
{
	return components.size();
}

std::vector<GameComponent*> GameObject::getComponents()
{
	return components;
}

GameComponent* GameObject::getComponentByIndex(U32 index)
{
	return index < components.size() ? components.at(index) : nullptr;
}

GameComponent* GameObject::getComponentByID(U32 ID)
{
	for (auto c : components) if (c->ID == ID) return c;
	return nullptr;
}

std::vector<GameComponent*> GameObject::getComponentsOfType(U32 typeID)
{
	std::vector<GameComponent*> res;
	for (auto c : components) if (c->getType() == typeID) res.push_back(c);
	return res;
}

GameComponent* GameObject::getComponentOfType(U32 typeID)
{
	for (auto c : components) if (c->getType() == typeID) return c;
	return nullptr;
}

bool GameObject::isComponentOf(const GameComponent* c) const
{
	return c->getParent() == this;

}

//Debug check, is it really necessary
void GameObject::deleteChild(GameObject** g)
{
	if (!isChild(*g)) return;
	for (auto i = children.begin(); i != children.end(); ++i) {
		if (*i == *g) {
			children.erase(i);
			break;
		}
	}
	delete *g;
	
}

void GameObject::moveChild(GameObject* g, GameObject* newParent)
{
	if (!isChild(g)) return;
	newParent->addChild(g);
	for (auto i = children.begin(); i != children.end(); ++i) {
		if (*i == g) {
			children.erase(i);
			break;
		}
	}
}

void GameObject::deleteComponent(GameComponent** c)
{
	if (!isComponentOf(*c)) return;
	for (auto i = components.begin(); i != components.end(); ++i) {
		if (*i == *c) {
			components.erase(i);
			break;
		}
	}
	(*c)->free();
	delete *c;
}

GameObject* GameObject::getParent()
{
	return parent;
}

GameObject* GameObject::getRoot()
{
	if (parent == nullptr) return this;
	return parent->getRoot();
}

bool GameObject::isRoot() const
{
	return !parent;
}

Transform& GameObject::getTransform()
{
	return *transform;
}

std::string GameObject::getName() const
{
	return name;
}

void GameObject::addLoadedComponent(GameComponent* component)
{
	components.push_back(component);
}

bool GameObject::operator<(const GameObject& g)
{
	return ID < g.ID;
}

U32 GameObject::IDCounter = 0;







