#include "FreeMove.h"


COMPONENTREGISTER(FreeMove)

FreeMove::FreeMove() : GameComponent()
{
	type = TypeID<FreeMove>::getType();
}

void FreeMove::update()
{



	
	Vector2 motion = input->getMouseMotion();
	motion.y *= -1;

	float sensFactor = 80.f;
	
	motion /= sensFactor;



	float dDot = getTransform().getForward().dot(Vector3::WORLD_DOWN);
	float uDot = getTransform().getForward().dot(Vector3::WORLD_UP);


	if (dDot - motion.y > 0.9) {
		motion.y = -(0.9 - dDot);
	}

	if (uDot + motion.y > 0.9) {
		motion.y = 0.9 - uDot;
	}

	getTransform().rotate(Quaternion(Vector3::WORLD_UP, motion.x));
	getTransform().rotate(Quaternion(getTransform().getWorldLeft(), motion.y));

	
	F32 speed = 0.005f;


	if (input->isKeyActive(SDLK_LSHIFT)) {
		speed = 0.2f;
	}

	if (input->isKeyActive(SDLK_LCTRL)) {
		speed = 0.01f;
	}



	if (input->isKeyActive(SDLK_w)) {
		getParent()->getTransform().translate(getParent()->getTransform().getWorldForward() * speed);

	}

	if (input->isKeyActive(SDLK_s)) {
		getParent()->getTransform().translate(getParent()->getTransform().getWorldBack() * speed);
	}

	if (input->isKeyActive(SDLK_a)) {
		getParent()->getTransform().translate(getParent()->getTransform().getWorldLeft() * speed);
	}
	
	if (input->isKeyActive(SDLK_d)) {
		getParent()->getTransform().translate(getParent()->getTransform().getWorldRight() * speed);
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
	
}

