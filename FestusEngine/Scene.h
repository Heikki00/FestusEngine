#pragma once

class GameObject;

//Interface that represents a single scene in the game. 
class Scene {
public:

	virtual ~Scene() = default;

	//Inits the scene
	virtual void init() = 0;

	//Updates the scene
	virtual void update() = 0;

	//Renders the scene
	virtual void render() = 0;

	//Re-activates the scene after scene change
	virtual void activate() {};

	//De-activates the scene after scene change
	virtual void deactivate() {};

	U32 getType() const { return type; }

protected:
	GameObject* root;
	U32 type;

};