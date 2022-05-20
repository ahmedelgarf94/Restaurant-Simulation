#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"


PromotionEvent::PromotionEvent(int eTime, int oID, double exmo) :Event(eTime, oID)
{
	OrderID = oID; //the id of the order we need to promote
	ExtraMoney = exmo; //the extra money that the client pay to promote the order
	EventTime = eTime; //the time step that the event will take place
}
//***************************

//***************************




void PromotionEvent::Execute(Restaurant* pRest)
{
	//pRest->getOrderQueue();
	Order* pOrd = pRest->FindID(OrderID); //search for the id 
	if (!pOrd)
	{
		return;
	}
	else
	{
		pOrd->SetType(TYPE_VIP); //change the type from normal to vip order
		pOrd->setTotalMoney(pOrd->getTotalMoney() + ExtraMoney); //update the total money of the order
		pRest->Promote(pOrd);//increment number of VIP orders and decrement the normal Orders and move the order from Norml LinkedList to VIP queue
		//pRest->DistributeOrders();
		//pRest->getOrderQueue();
	}
}
