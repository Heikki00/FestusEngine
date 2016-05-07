#pragma once
#include "Physics.h"


void Physics::addTile(TilePhysics* tile)
{
	tiles.push_back(tile);
}

void Physics::removeTile(TilePhysics* tile)
{
	for (auto i = tiles.begin(); i != tiles.end(); ++i) {
		if (*i == tile) {
			tiles.erase(i);
			break;
		}


	}


}

void Physics::update()
{

	
	for (TilePhysics* tile : tiles) {

		Vector2 tilePos = Vector2(tile->getTransform().getWorldPosition());
		tile->setMomentum(tile->getMomentum() + (ftime->getDeltaTime() * tile->getAcceleration()));
		
		Vector2 tileNewPos = tilePos + (ftime->getDeltaTime() * tile->getMomentum());

		for (TilePhysics* testingTile : tiles) {

			if (testingTile == tile) continue;

			Vector2 testingTilePos = Vector2(testingTile->getTransform().getWorldPosition());
			Vector2 testingMin = testingTilePos - Vector2(testingTile->getSize() / 2.f);
			Vector2 testingMax = testingTilePos + Vector2(testingTile->getSize() / 2.f);
			
			if (tileNewPos.x > testingMin.x && tileNewPos.x < testingMax.x && tileNewPos.y > testingMin.y && tileNewPos.y < testingMax.y) {
				

				if (tile->getMass() != 0) {

					Vector2 separation = tileNewPos - testingTilePos;

					Vector2 normal;

					if (abs(separation.x) > abs(separation.y)) {
						if (separation.x < 0) normal = Vector2(-1, 0);
						else normal = Vector2(1, 0);
					}
					else {
						if (separation.y < 0) normal = Vector2(0, -1);
						else normal = Vector2(0, 1);
					}

					Vector2 newMomentum(tile->getMomentum() - (2 * tile->getMomentum().dot(normal) * normal));

					if (normal.x == 0) {
						newMomentum.y *= tile->getBounciness() + testingTile->getBounciness();
						
					}
					else {
						newMomentum.x *= tile->getBounciness() + testingTile->getBounciness();
					}
					
					tile->setMomentum(newMomentum);
					tile->setAcceleration(newMomentum.normalized() * tile->getAcceleration().lenght());

				}
				
				tile->setMomentum(Vector2(0));
				tile->setAcceleration(Vector2(0));




			}



		}
		
		tile->getTransform().setPosition(Vector3(tileNewPos.x, tileNewPos.y, 0.f));

	}





}
