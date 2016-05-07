#pragma once
#include "GameComponent.h"





class FreeMove : public GameComponent{

public:

	FreeMove();

	void update() override;

	virtual MappedValues* save() override;

	virtual void load(const MappedValues& map);




	COMPONENTLOADCONSTRUCTOR(FreeMove)


};