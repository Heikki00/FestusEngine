#include "RenderingEngine.h"
#include "RenderLayer.h"
#include "Window.h"

RenderingEngine::RenderingEngine()
{
	camera = nullptr;

	glClearColor(0, 0, 0, 1);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);

	samplerSlots["diffuse"] = 1;
	samplerSlots["normal"] = 2;
	samplerSlots["displacement"] = 3;
	samplerSlots["gBuffer_0"] = 4;
	samplerSlots["gBuffer_1"] = 5;
	samplerSlots["gBuffer_2"] = 6;
	samplerSlots["gBuffer_3"] = 7;

	guiLayer = nullptr;
	GUIEnabled = true;
}

RenderingEngine::~RenderingEngine()
{
	for (RenderLayer* r : layers) {
		delete r;
	}
	
	delete guiLayer;

}

void RenderingEngine::render(GameObject* root)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	for (auto l : layers) {
		currentLayer = l;
		l->render(root);
	}

	
	if (guiLayer && GUIEnabled) {
		currentLayer = guiLayer;
		guiLayer->render(root);
	}
	currentLayer = nullptr;

	

	window->swapBuffers();
}

U32 RenderingEngine::addLayer(RenderLayer* r)
{
	
	layers.push_back(r);
	return layers.size() - 1;
}

void RenderingEngine::insertLayer(RenderLayer* r, U32 index)
{
	layers.insert(layers.begin() + index, r);
}

void RenderingEngine::removeLayer(U32 index)
{
	delete layers.at(index);
	layers.erase(layers.begin() + index);
}

void RenderingEngine::setGUILayer(RenderLayer* r)
{
	if (guiLayer == nullptr) delete guiLayer;
	guiLayer = r;
}

RenderLayer* RenderingEngine::getGUILayer()
{
	return guiLayer;
}

bool RenderingEngine::isGUIEnabled()
{
	return GUIEnabled && (guiLayer != nullptr);
}

void RenderingEngine::enableGUI()
{
	GUIEnabled = true;
}

void RenderingEngine::disableGUI()
{
	GUIEnabled = false;
}

U32 RenderingEngine::getNumLayers()
{
	return layers.size() + 1;
}

RenderLayer* RenderingEngine::getCurrentLayer()
{
	return currentLayer;
}

U32 RenderingEngine::getSamplerslot(const string& name)
{
	return samplerSlots[name];
}

void RenderingEngine::setCamera(Camera* camera)
{
	this->camera = camera;
}

Camera* RenderingEngine::getCamera()
{
	return camera;
}

void RenderingEngine::addLight(BaseLight* light)
{
	lights.push_back(light);
}

void RenderingEngine::removeLight(BaseLight* light)
{
	for (auto i = lights.begin(); i != lights.end();i++) {
		if (*i == light) {
			lights.erase(i);
			return;
		}
	}
}

std::vector<BaseLight*>& RenderingEngine::getLights()
{
	return lights;
}
