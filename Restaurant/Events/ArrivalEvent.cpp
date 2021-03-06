#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}
//*********************************************************************************
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int oSize, double oMoney) : Event(eTime, oID)
{
	OrdType = oType;
	OrdMoney = oMoney;
	OrdSize = oSize;
}
//*********************************************************************************

void ArrivalEvent::Execute(Restaurant* pRest)
{
	
	Order* pOrd = new Order(OrderID, OrdType, OrdMoney, OrdSize, EventTime);
	pRest->AddtoOrderQueue(pOrd);
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	

	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	//Order* pOrd = new Order(OrderID,OrdType);
	//pRest->AddtoDemoQueue(pOrd);
}
