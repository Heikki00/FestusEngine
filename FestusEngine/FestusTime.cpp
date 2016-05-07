#pragma once
#include "FestusTime.h"

U32 FestusTime::getTime()
{
	return SDL_GetTicks();
}

F32 FestusTime::getDeltaTime()
{
	return delta;
}

