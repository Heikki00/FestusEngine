#pragma once
#include "GameComponent.h"
#include "SaveManager.h"
class RenderingEngine;
class ShaderStage;
class CoreEngine;

//Node of the scene graph. Contain children(witch can have their own children) and components. Components will 
//define the behavior of the game object. Only allocate to heap, never to stack
class GameObject {
public:


	
	GameObject(const std::string& name);
	
	~GameObject();


	//Adds child to this node. everything done to this node, will be done to all children
	void addChild(GameObject* child);

	//Adds component to this node. Components define behavior of the node. When node's update() is called, components update() is called etc.
	void addComponent(GameComponent* component);



	//Calls render() for all components of this GameObject.
	void render(U32 renderType);

	//Calls update() for all components of this GameObject.
	void update();

	//Calls render() for all components and children. Shader is shader to be used in rendering.
	void renderAll(U32 renderType);

	//Calls update() for all components and children
	void updateAll();

	//Calls save() of every component and child, compiles and returns the results
	ObjectSaveData save();


	//Returns the number of direct children this GameObject has(children.size())
	U32 getNumChildren() const;

	//Returns direct children of this GameObject
	std::vector<GameObject*> getChildren();
	
	//Returns child by index. First child is index 0, second is 1, etc. Nothing to do with ID. If index >= children.size() returns nullptr.
	GameObject* getChildByIndex(U32 index);

	//Returns child by name. Returns nullptr if a child with the given name was not found.
	GameObject* getChildByName(const string& name);

	//Returns true if the GameObject is direct child of this one
	bool isChild(const GameObject* g) const;



	//Returns the number of GameObjects that are attached to this one
	U32 getNumAttached() const;

	//Returns all GameObjects attached to this one(children, grandchildren, etc.)
	std::vector<GameObject*> getAllAttached();

	//Searches for GameObject that is attached to this one by ID.
	GameObject* getAttachedByID(U32 ID);

	//Returns true if g is attached to this one
	bool isAttached(const GameObject* g) const;



	//Returns the number of components
	U32 getNumComponents() const;

	//Returns all components of this GameObject
	std::vector<GameComponent*> getComponents();

	//Returns component by index
	GameComponent* getComponentByIndex(U32 index);

	//returns component by ID
	GameComponent* getComponentByID(U32 ID);
	
	//Returns vector of components of type typeID
	std::vector<GameComponent*> getComponentsOfType(U32 typeID);

	//Returns the first component of type typeID, or nullptr if there is none
	GameComponent* getComponentOfType(U32 typeID);

	//Returns the first component of type T
	template<class T>
	T* getComponentOfType() {
		for (GameComponent* c : components) {
			if (c->type == TypeID<T>::getType()) return static_cast<T*>(c);

		}
		return nullptr;

	};

	//Returns vector of components of type T
	template<class T>
	std::vector<T*> getComponentsOfType() {
		std::vector<T*> res;

		for (GameComponent* c : components) {
			if (c->type == TypeID<T>::getType()) res.push_back(static_cast<T*>(c));

		}
		return res;

	}

	//Returns true if c id component of this GameObject
	bool isComponentOf(const GameComponent* conc) const;



	//Deletes g if it is child of this GameObject
	void deleteChild(GameObject** g);
	
	//Removes g form GameObjects children and adds it to newParents children
	void moveChild(GameObject* g, GameObject* newParent);

	//Deletes c if it is component of this GameObject
	void deleteComponent(GameComponent** c);


	GameObject* getParent();

	bool isRoot() const;

	//Returns reference to Transform object of this GameObject. Object can be freely modified;
	Transform& getTransform();


	std::string getName() const;

	//Unique ID
	const U32 ID;
	
	bool operator <(const GameObject& g);;


protected:




private:

	//Parent of this GameObject. If This GameObject is root, parent == nullptr
	GameObject* parent;

	//Children of this GameObject
	std::vector<GameObject*> children;

	//Components of this GameObject
	std::vector<GameComponent*> components;

	//Transform of this GameObject
	Transform* transform;
	
	//Name of this GameObject
	std::string name;

	static U32 IDCounter;
};



