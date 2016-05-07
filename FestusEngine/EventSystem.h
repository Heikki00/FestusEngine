#pragma once



//Node in EventSystem's linked lists
struct EventNode {
	EventNode* prev;
	EventNode* next;

	Event* event;

	EventNode(): prev(nullptr), next(nullptr), event(nullptr) {}


	~EventNode() {

		if (event) delete event;
	}

};

//Class that is used to communicate events between components and systems. Events can be added and found.
//When an event is added, it's actually visible added in seperate linked list. New events become visible at the start of each frame.
//This is done to assure that every component can see the event for same amount of frames(even if event is added from component in mid-update)
class EventSystem {
public:

	//Creates the linked lists
	EventSystem();

	~EventSystem();

	//Queues event e to be added at the start of the next frame
	void addEvent(Event* e);

	//Returns a vector of events that have the specified type;
	std::vector<Event*> findEvents(const string& type);

	//Returns the first event of the specified type, or nullptr if there are none.
	Event* findEvent(const string& type);

	//Returns true if EventSystem contains any events of specified type. Faster than findEvents.
	bool hasEvent(const string& type);


protected:

	friend class CoreEngine;

	//Updates the ages of the frames, removes some, adds new events
	void update();

private:

	EventNode* head;
	EventNode* tail;

	EventNode* bufferHead;
	EventNode* bufferTail;

};