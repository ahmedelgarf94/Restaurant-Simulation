#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include "Cook.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money
	int ArrTime, ServTime, FinishTime, WaitingTime;	//arrival, service start, and finish times
	//****************************************************************************
	int OrderSize;  //The number of dishes in the order
	double Pri; //The priority of the VIP orders according to the priority equation
	//int CookID;
	int startServingTime;
	Cook* pCook;
	//****************************************************************************
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type);
	//*****************************************************************************
	Order(int id, ORD_TYPE r_Type, double Money, int Size, int ArrivalTime);
	Order(int id, ORD_TYPE r_Type, int eTime);
	void SetID(int id);
	void SetType(ORD_TYPE t);
	void setTotalMoney(double tm);
	double getTotalMoney() const;
	void setArrivalTime(int at);
	int getArrivalTime();
	void setServiceTime(int st);
	int getServiceTime() const;
	void setStartService(int time);
	int getStartService() const;
	void setFinishTime(int ft);
	int getFinishTime() const;
	void setOrderSize(int os);
	int getOrderSize() const;
	double Priority(); //function to calculate the priority of the VIP orders according to the priority equation 
	//int getCookID();
	//void setCookID(int id);
	Cook* getpCook();
	void setpCook(Cook* Cook);
	void setWaitingTime(int time);
	int getWaitingTime();
	//*****************************************************************************
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif