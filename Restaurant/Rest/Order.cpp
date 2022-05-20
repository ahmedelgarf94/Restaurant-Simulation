#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}
//*********************************************************************************
Order::Order(int id, ORD_TYPE r_Type, double Money, int Size, int ArrivalTime)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	totalMoney = Money;
	OrderSize = Size;
	ArrTime = ArrivalTime;
	status = WAIT;
	Distance = 0;
	Pri = 0;
	startServingTime = 0;
	FinishTime = 0;
	ServTime = 0;
	WaitingTime = 0;
	pCook = nullptr;
}
Order::Order(int id, ORD_TYPE r_Type, int eTime)
{
	ID = id;
	type = r_Type;
}
void Order::SetID(int id)
{
	ID = id;
}

void Order::SetType(ORD_TYPE t)
{
	type = t;
}

void Order::setTotalMoney(double tm)
{
	totalMoney = tm;
}
double Order::getTotalMoney() const
{
	return totalMoney;
}
void Order::setArrivalTime(int at)
{
	ArrTime = at;
}
int Order::getArrivalTime() 
{
	return ArrTime;
}
void Order::setServiceTime(int st)
{
	ServTime = st;
}
int Order::getServiceTime() const
{
	return ServTime;
}
void Order::setStartService(int time)
{
	startServingTime = time;
}
int Order::getStartService() const
{
	return startServingTime;
}
void Order::setFinishTime(int ft)
{
	FinishTime = ft;
}
int Order::getFinishTime() const
{
	return FinishTime;
}
void Order::setOrderSize(int os)
{
	OrderSize = os;
}
int Order::getOrderSize() const
{
	return OrderSize;
}
/*void Order::setCookID(int id)
{
	CookID = id;
}
int Order::getCookID() 
{
	return CookID;
}*/
Cook* Order::getpCook()
{
	return pCook;
}
void Order::setpCook(Cook* Cook)
{
	pCook = Cook;
}
void Order::setWaitingTime(int time)
{
	WaitingTime = time;
}
int Order::getWaitingTime()
{
	return WaitingTime;
}
double Order::Priority() //function to calculate the priority of the VIP orders according to the priority equation 
{
	if (type == TYPE_VIP)
	{
		Pri = (4 * totalMoney) + (3 * (double)OrderSize) + (2 * (double)Distance) + (1 / (double)ArrTime) - (ID/1000000.00);
		return Pri;
	}
	else
		return 0;
}

//*********************************************************************************

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

