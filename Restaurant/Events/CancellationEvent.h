
#pragma once


#include "Event.h"
class Restaurant;
class Event;

//class for the arrival event
class CancellationEvent : public Event
{
	int Size;
	double Money;
	//int LeavingTime;
public:
	CancellationEvent(int eTime, int oID);
	//*******************************************************************************
	virtual void Execute(Restaurant* pRest);	//override execute function

};