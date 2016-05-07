#pragma once
#include "TilePhysics.h"



class Physics {
public:


	void addTile(TilePhysics* tile);

	void removeTile(TilePhysics* tile);

	void update();

	

private:
	std::vector<TilePhysics*> tiles;


};