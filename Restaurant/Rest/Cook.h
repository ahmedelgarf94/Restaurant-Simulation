#pragma once

#include "..\Defs.h"
//#include "Order.h"
class Order;
//#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int Speed;		//dishes it can prepare in one clock tick (in one timestep)
	COOK_STATUS status;
	//***************************************************************************************************
	Order* pOrd;
	int StartBreak;
	int Break;
	int numDoneOrders;
	int PausedBreakTime;
	int ResumedBreakTime;
	int SpeedBeforeINJ;
	int EndBreak;
	//***************************************************************************************************

public:
	Cook();
	//**********************************************************************************************
	Cook(ORD_TYPE, int, int, int); // pCook = new Cook(TYPE_VIP, Speed_Of_VIP_Cooks, BO, BV);

	
	//Cook(int, int, int, int, int, int, int, int, int);
	int GetSpeed();
	void setSpeed(int s);
	int GetnumDoneOrders();
	void setnumDoneOrders(int num);
	int GetStartBreak();
	void setStartBreak(int time);
	int GetBreak();
	void setBreak(int time);
	void setCookStatus(COOK_STATUS s);
	COOK_STATUS getCookStatus();
	void setPausedBreak(int timestep); //changed
	int getPausedBreak();
	void setResumedBreak(int timestep);
	int getResumedBreak();
	Order* GetpOrder();
	void setpOrder(Order* Order);
	void setSpeedBeforeINJ(int s);
	int getSpeedBeforeINJ();
	void setEndBreak(int t);
	int getEndBreak();
	//**************************************************************************************************
	virtual ~Cook();
	int GetID();  
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	

};
