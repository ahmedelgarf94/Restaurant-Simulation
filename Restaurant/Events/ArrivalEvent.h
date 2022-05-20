#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"
class Restaurant;

//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP	                
	double OrdMoney;	//Total order money
	//***************************************************************
	int OrdSize;
	//***************************************************************
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	//Add more constructors if needed
	//*******************************************************************************
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int oSize, double oMoney);
	//*******************************************************************************
	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif