#pragma once
#include "stdafx.h"
#include "variable.h"


void insertEvent(sf::Sprite *name)
{
	PFEVENT *Event = new PFEVENT;
	Event->objectName = name;
	Event->next = EventsHead;
	EventsHead = Event;
}