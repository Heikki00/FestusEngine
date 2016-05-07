#pragma once
#include "TilePhysics.h"



TilePhysics::TilePhysics(F32 size, F32 mass, F32 friction, F32 bounciness)
{
	type = TypeID<TilePhysics>::getType();

	physics->addTile(this);

}



void TilePhysics::update()
{

}

F32 TilePhysics::getSize() const
{
	return size;
}
