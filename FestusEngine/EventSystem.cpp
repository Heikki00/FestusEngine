#include "EventSystem.h"


EventSystem::EventSystem()
{
	head = new EventNode;
	tail = new EventNode;

	head->next = tail;
	tail->prev = head;

	bufferHead = new EventNode;
	bufferTail = new EventNode;
	bufferHead->next = bufferTail;
	bufferTail->prev = bufferHead;

}

EventSystem::~EventSystem()
{
	EventNode* e = head;

	while (e != nullptr) {
		e = e->next;
		if(e)delete e->prev;
	
	}

	e = bufferHead;

	while (e != nullptr) {
		e = e->next;
		if (e) delete e->prev;

	}

	delete tail;

	delete bufferTail;

}

void EventSystem::addEvent(Event* e)
{
	EventNode* en = new EventNode;
	en->event = e;
	
	en->prev = bufferTail->prev;
	en->next = bufferTail;

	bufferTail->prev->next = en;
	bufferTail->prev = en;

	
}

std::vector<Event*> EventSystem::findEvents(const string& type)
{
	U32 typeID = Event::enumTypeIDs[type];
	std::vector<Event*> res;

	if (typeID == 0) return res;

	EventNode* e = head->next;


	while (e != tail) {
		if (e->event->getType() == typeID) {
			res.push_back(e->event);
		}

		e = e->next;

	}

	return res;

}

Event* EventSystem::findEvent(const string& type)
{
	U32 typeID = Event::enumTypeIDs[type];
	if (typeID == 0) return nullptr;

	

	EventNode* e = head->next;



	while (e != tail) {
		if (e->event->getType() == typeID) {
			return e->event;
		}

		e = e->next;

	}
	return nullptr;

}

bool EventSystem::hasEvent(const string& type)
{
	U32 typeID = Event::enumTypeIDs[type];

	EventNode* e = head->next;


	while (e != tail) {
		if (e->event->getType() == typeID) {
			return true;
		}

		e = e->next;

	}

	return false;

}

void EventSystem::update()
{


	EventNode* e = head->next;
	
	bool shouldDelete = false;

	while (e != tail) {
		
		//Age the event. New events are added after this, so everyone has at least one frame
		e->event->frameAge++;
		e->event->realAge += ftime->getDeltaTime();
		
		shouldDelete = false;



		
		switch (e->event->getLifetimeType())
		{
		case Event::FRAMETIME: {
			
			//If their thime has come, remove and delete
			if (e->event->frameAge >= e->event->getLifetimeNumber()) {
				e->prev->next = e->next;
				e->next->prev = e->prev;
				shouldDelete = true;
				
			}

			
			break;



		}

		case Event::REALTIME: {
			//If their thime has come, remove and delete
			if (e->event->realAge >= (F32)e->event->getLifetimeNumber()) {
				e->prev->next = e->next;
				e->next->prev = e->prev;
				shouldDelete = true;
			}

			break;

		}
		//Event::INFINITY, basically
		default: break;

		}

		EventNode* temp = e;
		e = e->next;
		
		if (shouldDelete) delete temp;

	}

	//Move the queued events to main list


		tail->prev->next = bufferHead->next;
		bufferHead->next->prev = tail->prev;

		bufferTail->prev->next = tail;
		tail->prev = bufferTail->prev;

		bufferHead->next = bufferTail;
		bufferTail->prev = bufferHead;








}

