#include "FreeMove.h"


COMPONENTREGISTER(FreeMove)

FreeMove::FreeMove() : GameComponent()
{
	type = TypeID<FreeMove>::getType();
}

void FreeMove::update()
{
	
	
	
	
	F32 speed = 0.5f;


	if (input->isKeyActive(SDLK_LSHIFT)) {
		speed = 0.2f;
	}

	if (input->isKeyActive(SDLK_LCTRL)) {
		speed = 0.01f;
	}


	F32 maxSpeed = 0.5f;


	if (input->isKeyActive(SDLK_w)) {
		//FIX IMPLEMENT LOOKUP BY TYPE ID
		Vector2 mom = static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->getAcceleration() + (Vector2(0, 1) * speed);


		if (mom.lenght2() > maxSpeed * maxSpeed) {
			mom.normalize();
			mom *= maxSpeed;
		}

		static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->setMomentum(mom);

	}

	if (input->isKeyActive(SDLK_s)) {
		Vector2 mom = static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->getAcceleration() + (Vector2(0, -1) * speed);


		if (mom.lenght2() > maxSpeed * maxSpeed) {
			mom.normalize();
			mom *= maxSpeed;
		}

		static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->setMomentum(mom);
	}

	if (input->isKeyActive(SDLK_a)) {
		Vector2 mom = static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->getAcceleration() + (Vector2(-1, 0) * speed);


		if (mom.lenght2() > maxSpeed * maxSpeed) {
			mom.normalize();
			mom *= maxSpeed;
		}

		static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->setMomentum(mom);
	}
	
	if (input->isKeyActive(SDLK_d)) {
		Vector2 mom = static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->getAcceleration() + (Vector2(1, 0) * speed);


		if (mom.lenght2() > maxSpeed * maxSpeed) {
			mom.normalize();
			mom *= maxSpeed;
		}

		static_cast<TilePhysics*>(getParent()->getComponentByIndex(0))->setMomentum(mom);
	}


	


	if (input->isKeyActive(SDLK_e)) {
		Event* e = new Event("PLAYER_ACTION", 1.f, Event::REALTIME);

		eventSystem->addEvent(e);
	}



	


}

MappedValues* FreeMove::save()
{
	MappedValues* m = new MappedValues;
	m->setString("type", "FreeMove");
	return m;
}

void FreeMove::load(const MappedValues& map)
{
	type = TypeID<FreeMove>::getType();
}

