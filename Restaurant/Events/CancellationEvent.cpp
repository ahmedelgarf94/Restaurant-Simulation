#include "CancellationEvent.h"

#include "..\Rest\Restaurant.h"


//***************************

//***************************
CancellationEvent::CancellationEvent(int eTime, int oID) :Event(eTime, oID)
{

	Size = 0;
	Money = 0;
}

void CancellationEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order 
	//pRest->getOrderQueue();
	Order* pOrd= pRest->FindID(OrderID);
	if (!pOrd)
	{
		return;
	}
	else
	{
		pRest->CancelOrder(pOrd);
	}
}
