#pragma once
#include "Scene.h"



class GameScene : public Scene {
public:

	GameScene();

	virtual void init() override;

	~GameScene();

	virtual void update() override;

	virtual void render() override;

	virtual void activate() override;

	virtual void deactivate() override;



};