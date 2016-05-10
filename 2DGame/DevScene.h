#pragma once
#include "Scene.h"

class DevScene : public Scene {
public:

	DevScene();
	
	~DevScene();

	virtual void init() override;

	virtual void update() override;

	virtual void render() override;

	virtual void activate() override;

	virtual void deactivate() override;

private:



};