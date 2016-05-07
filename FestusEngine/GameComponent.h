#pragma once



#define GAMECOMPONENTH

#define COMPONENTREGISTER(T) struct MacroComponentRegisteration##T{MacroComponentRegisteration##T(){ SaveManager::registerLoad(#T, ##T::_get_load_instance);}};MacroComponentRegisteration##T __staticMacrocomponent##T;

#define COMPONENTLOADCONSTRUCTOR(T) protected: friend class SaveManager; friend struct MacroComponentRegisteration##T; static GameComponent* _get_load_instance(){return reinterpret_cast<T*>(new U8[sizeof(T)]);}public:


class ShaderStage;
class CoreEngine;
class RenderingEngine;
class GameObject;
class Transform;




//Interface for user-defined components that can be added to GameObject.
class GameComponent {
public:
	GameComponent() : ID(++GameComponent::IDCounter) { };

	virtual ~GameComponent() = default;

	//Inits the GameComponent, does not have to be overridden. Called when the component is added to a object. Use this instead of constructor, since the parent pointer is set after constructor
	virtual void init() {}

	//Frees all of the GameComponent's resources, called upon parents deletion or the component's removal. Does not have to be overridden
	virtual void free(){}

	//Virtual function, update component. Does not have to be overridden.
	virtual void update() {}




	//Virtual function, used in rendering. Does not have to be overridden.
	virtual void render(U32 renderType) {}

	//Function that compresses the whole object into key-value pairs, of witch it can be decomposed later. Called relatively rarely, and must be implemented
	virtual MappedValues* save() = 0;

	//Function that gives the class the generated save-data, and sets the appropriate values in the class. Called after setting the parent.
	virtual void load(const MappedValues& map) = 0;

	GameObject* getParent() const;

	//Shortcut to getParent()->getTransform()
	Transform& getTransform();

	
	//Returns the type of this component
	U32 getType() const;
	
	//Unique ID
	const U32 ID;


protected:
	
	//Type of this component
	U32 type;

	//Sets parent of this component. Only call this once, from GameObject
	void setParent(GameObject* parent);

	friend class GameObject;

private:
	
	
	GameObject* parent;

	static U32 IDCounter;

	
};





