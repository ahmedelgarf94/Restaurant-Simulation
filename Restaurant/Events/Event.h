#ifndef __EVENT_H_
#define __EVENT_H_

#include "..\Defs.h"

class Restaurant;	//Forward declation
class ArrivalEvent;
class CancellationEvent;

//The base class for all possible events in the system (abstract class)
class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order
	//***********************************************************************
	//ORD_TYPE OrderType;  //the order type (N: normal, G: vegan, V: VIP). 
	//char EventType;         //letter means Type of event.
	//int Size;               // the number of dishes of the order 
	//int Money;              // the total order money. 
	//int NumberOfEvents;
	//***********************************************************************

public:
	Event(int eTime, int ordID);
	int getEventTime();
	int getOrderID();
	virtual ~Event();
	//**************************************************************************************
	//char getOrderType();
	//char getEventType();
	//int getSize();
	//int getMoney();

	//**************************************************************************************

	virtual void Execute(Restaurant* pRest)=0;	////a pointer to "Restaurant" and events need it to execute

};


#endif