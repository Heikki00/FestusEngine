#pragma once
#include "EventResponder.h"

COMPONENTREGISTER(EventResponder)

EventResponder::EventResponder()
{
	type = TypeID<EventResponder>::getType();
}

void EventResponder::update()
{
	
	Event* e = eventSystem->findEvent("PLAYER_ACTION");

	if (e) {
		I32 r1 = (rand() % 6) - 3;
		I32 r2 = (rand() % 6) - 3;
		I32 r3 = (rand() % 6) - 3;
		getTransform().translate(Vector3(r1, r2, r3));
	
	}




}

MappedValues* EventResponder::save()
{
	MappedValues* m = new MappedValues;
	m->setString("type", "EventResponder");
	return m;
}

void EventResponder::load(const MappedValues& map)
{
	type = TypeID<EventResponder>::getType();
}
