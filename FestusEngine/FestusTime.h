#pragma once


//Class that can be used to retrive current time, and the time used to do last frame
class FestusTime {
public:

	//Returns amount of millisecond after initialization
	U32 getTime();

	//Returns the time used to do last frame
	F32 getDeltaTime();

protected:
	friend class CoreEngine;

	F32 delta;


};