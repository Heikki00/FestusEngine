#pragma once
#include "Game.h"
#include "GameObject.h"

class TestGame : public Game {
public:

	virtual void init() override;
	
	~TestGame();

	virtual void update() override;

	virtual void render() override;

};