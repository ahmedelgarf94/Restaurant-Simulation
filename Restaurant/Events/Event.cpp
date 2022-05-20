#include "Event.h"


Event::Event(int eTime, int ordID)
{
	EventTime = eTime;
	OrderID	= ordID;
}


int Event::getEventTime()
{
	return EventTime;
}
int Event::getOrderID()
{
	return OrderID;
}

//***********************************************************************************************
/*int Event::getSize()
{
	return Size;
}*/
/*int Event::getMoney()
{
	return Money;
}*/
/*char Event::getEventType()
{
	return EventType;
}*/
/*char Event::getOrderType()
{
	return OrderType;
}*/
//***********************************************************************************************


Event::~Event()
{

}

