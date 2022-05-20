#pragma once
#include "Event.h"
//class for the arrival event
class PromotionEvent : public Event
{
	double ExtraMoney;	// order Extramoney

	//*********************
public:
	PromotionEvent(int eTime, int oID, double exmo);
	//***************************

	virtual void Execute(Restaurant* pRest);	//override execute function

};
