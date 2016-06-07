#pragma once
#include "GameObject.h"





//Interface that does all of the rendering. RenderingEngine contains a list of TenderLayers, and calls their render functions. These render functions can render anything they want, blend the result to the
//image rendered by previous RenderLayers, overwrite the old image, ignore the root, basically do whatever they want
class RenderLayer : public MappedValues
{
public:

	virtual ~RenderLayer() = default;



	//Function for rendering the frame
	virtual void render(GameObject* root) = 0;



};
