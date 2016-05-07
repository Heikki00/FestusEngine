#pragma once

#include "GameObject.h"
#include "RenderLayer.h"
#include "Camera.h"

class RenderLayer;
class BaseLight;

//Class that manages rendering. RenderingEngine inherits MappedValues, so it manages all constants related to rendering, ambient light for example(these values can be retrieved to shaders with R_)
//RenderingEngine has a list of RenderLayers. Each of these layers contain render function, and they are called in order. This class also has a static RenderLayer, that is always positioned last(meant for UI)
//RenderingEngine's constructor inits a list of samplerSlots. These are used for binding textures, and can re retrieved from RenderingEngine.
//RenderingEngine contains a pointer to camera that's used for rendering, and this camera can be set from here
class RenderingEngine : public MappedValues{
public:

	
	RenderingEngine();

	~RenderingEngine();


	//Calls all layer's(static last) render function with root
	void render(GameObject* root);



	//Adds layer to the list.
	U32 addLayer(RenderLayer* r);
	
	//Inserts layer to index, growing the amount of layers by one
	void insertLayer(RenderLayer* r, U32 index);
	
	//Removes and deletes the layer at index
	void removeLayer(U32 index);

	//Sets the gui layer, that gets called last. Passing nullptr to this function disables the use of gui layer
	void setGUILayer(RenderLayer* r);
	
	//Returns the gui layer, or nullptr if there isn't one
	RenderLayer* getGUILayer();

	//Returns true if there is a GUI layer and it is enabled
	bool isGUIEnabled();;

	//Enables the GUI layer
	void enableGUI();;

	//Disables the GUI layer. This does not delete it, but just disables it temporarily
	void disableGUI();;

	//Returns the number of layers(NOT including the static layer)
	U32 getNumLayers();

	//Returns the layer that's currently rendering, nullptr if not currently rendering
	RenderLayer* getCurrentLayer();

	//Returns the sampler slot bound to name, 0 if there is no set sampler slot
	U32 getSamplerslot(const string& name);


	//Sets the camera used for rendering
	void setCamera(Camera* camera);

	//Returns the camera used for rendering
	Camera* getCamera();


	void addLight(BaseLight* light);

	void removeLight(BaseLight* light);

	std::vector<BaseLight*>& getLights();




private:

	RenderLayer* guiLayer;
	RenderLayer* currentLayer;

	std::vector<RenderLayer*> layers;
	std::map<string, U32> samplerSlots;
	std::vector<BaseLight*> lights;

	bool GUIEnabled;

	Camera* camera;
};
