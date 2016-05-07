#pragma once
#include "Event.h"

Event::Event(const string& type, U32 lifetimeNum, U32 lifetimeType)
{
	//Find the ID, if this is first time, set it in the map
	auto i = enumTypeIDs.find(type);

	if (i->second == 0) i->second = ++enumTypeIDCounter;

	this->type = i->second;


	this->frameAge = 0;
	this->realAge = 0.f;
	this->lifetime = lifetimeNum | lifetimeType;
	

}

U32 Event::getType() const
{
	return type;
}

U32 Event::getLifetime() const
{
	return lifetime;
}

void Event::setLifetime(U32 lifetime)
{
	this->lifetime = lifetime;
}

U32 Event::getLifetimeNumber() const
{
	return ~Event::INFINITETIME & lifetime;
}

U32 Event::getLifetimeType() const
{
	return Event::INFINITETIME & lifetime;
}

F32 Event::getRealAge() const
{
	return realAge;
}

U32 Event::getFrameAge() const
{
	return frameAge;
}

std::map<string, U32> Event::enumTypeIDs;

U32 Event::enumTypeIDCounter = 1;

