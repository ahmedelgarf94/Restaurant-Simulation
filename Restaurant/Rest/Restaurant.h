#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Events\ArrivalEvent.h"
class ArrivalEvent;

#include "..\Events\CancellationEvent.h"

class CancellationEvent;
#include "..\Events\PromotionEvent.h"

#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	LinkedList<Event*> test;
	
	
	
	//***************************************************************************************
	LinkedList<Cook*>VIPLinkedList;
	LinkedList<Cook*>VeganLinkedList;
	LinkedList<Cook*>NormalLinkedList;
	//LinkedList<Cook*>AvailableCooks;    //Lists of all available cooks who are not assigned to an order
	LinkedList<Cook*>BusyCooks;         //Lists of all cooks who are assigned to an order
	LinkedList<Cook*>BreakCooks;        //Lists of all cooks who have break  

	//************************************
	PriorityQueue<Order*>VIPOrders;
	Queue<Order*>VeganOrders;
	//Queue<Order*>NormalOrders;
	LinkedList<Order*>NormalOrders;
	LinkedList<Order*>urgentOrders;    //List of all urgent orders
	//************************************
	//Queue<Cook*> VIPQueue;
	//Queue<Cook*> VeganQueue;
	//Queue<Cook*> NormalQueue;
	Queue<Order*> OrderQueue;
	int NumberOfEvents;
	int AutoPromotionLimit;
	int numNormalCooks;
	int numVeganCooks;
	int numVIPCooks;
	int numINJCooks;
	//int OrderID;
	int timestep;
	int BO;
	int total_waitingOrders;
	//****************************************************************************************
	LinkedList<Order*> InServiceList;                    //added
	LinkedList<Order*> DoneList;
	int numWaitingVeganOrd, numWaitingVIPOrd, numWaitingNormalOrd;
	int numServVeganOrd, numServVIPOrd, numServNormalOrd;
	int numUrgentOrd;
	int numAutoPromoted;
	int numNormPromoted;
	int RstPrd;
	double InjProp;
	int VIP_WT;
	int numDoneVIPOrd, numDoneVeganOrd, numDoneNormOrd;
	string filename;
	string messageID;
	//char EventType;
	//int isCanceled;
	//****************************************************************************************
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	


	void FillDrawingList();
	//*//******************************************
	void FileLoadingFunction();
	void AddtoOrderQueue(Order* pOrd);
	void CancelOrder(Order* pOrd);
	//void getOrderQueue();
	Order* FindID(int ID);
	//void DistributeOrders();
	void InsertService(Order* pOrd, Cook* pCook);  //added
	void DoneOrders();
	void Promote(Order* pOrd);
	bool AssignCook(Order *pOrd);
	void AutoPromotion();
	//void StepByStep();
	void FinishedCooks(Cook* pCook);
	void AssignOrder();
	void InABreak(Cook* pCook);
	void FinishBreak(int time);
	void InjuredCook(int timestep);
	double CalcAVG(int* arr, int size);
	void EndCooksBreak();
	void SortDoneOrders();
	void msgIDFunction(Order* pOrd);
	//void SilentMode();
	//void SortbyID();
//**********************************************************************************************
	// TODO: Add More Member Functions As Needed
	//


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	

/// ================================================================================================== 

	//***************************************************************************************************************
	void SimulationFunction(int x);
	//***************************************************************************************************************

};

#endif