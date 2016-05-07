#pragma once




class Event : public MappedValues{
public:

	Event(const string& type, U32 lifetimeNum, U32 lifetimeType);


	U32 getType() const;

	U32 getLifetime() const;

	void setLifetime(U32 lifetime);

	U32 getLifetimeNumber() const;

	
	U32 getLifetimeType() const;

	F32 getRealAge() const;

	U32 getFrameAge() const;



	
	enum {
		REALTIME = 0x80000000,
		FRAMETIME = 0x40000000,
		INFINITETIME = 0xC0000000
	};
	
protected:

	friend class EventSystem;

	F32 realAge;
	U32 frameAge;

private:

	U32 type;
	U32 lifetime;


	static std::map<string, U32> enumTypeIDs;
	static U32 enumTypeIDCounter;

};