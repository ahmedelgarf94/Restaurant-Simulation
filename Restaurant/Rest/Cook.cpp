#include "Cook.h"
#include "stdlib.h"
#include <cstdlib>
#include <ctime>


Cook::Cook()
{
}
//******************************************************************************
Cook::Cook(ORD_TYPE t, int s, int Brk, int id)  // pCook = new Cook(TYPE_VIP, Speed_Of_VIP_Cooks, BO, BV);
{
	type = t;
	Speed = s;
	Break =Brk;
	ID = id;
	numDoneOrders = 0;
	this->setCookStatus(AVB);
	//status = AVB;
	PausedBreakTime = 0; //changed
	ResumedBreakTime = 0;
	pOrd = nullptr;
	SpeedBeforeINJ = 0;
	EndBreak = 0;
}

/*Cook::Cook(int numNx, int numGx, int numVx, int SNx, int SGx, int SVx, int BNx, int BGx, int BVx)
{
	numN = (numNx > 0) ? numNx : 0;
	numG = (numGx > 0) ? numGx : 0;
	numV = (numVx > 0) ? numVx : 0;

	SN = (SNx > 0) ? SNx : 0;
	SG = (SGx > 0) ? SGx : 0;
	SV = (SVx > 0) ? SVx : 0;

	BN = (BNx > 0) ? BNx : 0;
	BG = (BGx > 0) ? BGx : 0;
	BV = (BVx > 0) ? BVx : 0;

}*/
void Cook::setSpeed(int s)
{
	Speed = s;
}

int Cook::GetSpeed()
{
	return Speed;
}
int Cook::GetnumDoneOrders()
{
	return numDoneOrders;
}
void Cook::setnumDoneOrders(int num)
{
	numDoneOrders = num;
}

void Cook::setStartBreak(int time)
{
	StartBreak = time;
}
int Cook::GetStartBreak()
{
	return StartBreak;
}

void Cook::setSpeedBeforeINJ(int s)
{
	SpeedBeforeINJ = s;
}
int Cook::getSpeedBeforeINJ()
{
	return SpeedBeforeINJ;
}

void Cook::setEndBreak(int t)
{
	EndBreak = t;
}
int Cook::getEndBreak()
{
	return EndBreak;
}
//*****************************************************************************

Cook::~Cook()
{
}


int Cook::GetID() 
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type; 
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}
int Cook::GetBreak()
{
	return Break;
}
void Cook::setBreak(int time)
{
	Break = time;
}

void Cook::setCookStatus(COOK_STATUS s)
{
	status = s;
}

COOK_STATUS Cook::getCookStatus()
{
	return status;
}

void Cook::setPausedBreak(int timestep) //changed
{
	PausedBreakTime = timestep;
}

int Cook::getPausedBreak()
{
	return PausedBreakTime;
}

void Cook::setResumedBreak(int timestep)
{
	ResumedBreakTime = timestep;
}
int Cook::getResumedBreak()
{
	return ResumedBreakTime;
}

Order* Cook::GetpOrder()
{
	return pOrd;
}
void Cook::setpOrder(Order* Order)
{
	pOrd = Order;
}

