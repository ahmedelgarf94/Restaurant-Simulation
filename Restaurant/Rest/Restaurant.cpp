#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
#include "Restaurant.h"
#include <fstream>
#include <cstdlib>
#include <ctime>


Restaurant::Restaurant()
{
	pGUI = NULL;
	//*****************************
	numNormalCooks = 0;    //Hannah
	numVeganCooks = 0;
	numVIPCooks = 0;
	numINJCooks = 0;
	total_waitingOrders = 0;
	numWaitingVeganOrd = 0;
	numWaitingVIPOrd = 0;
	numWaitingNormalOrd = 0;
	numUrgentOrd = 0;
	numDoneNormOrd = 0;
	numDoneVeganOrd = 0;
	numDoneVIPOrd = 0;
	numAutoPromoted = 0;
	timestep = 0;
	numServNormalOrd = 0;
	numServVeganOrd = 0;
	numServVIPOrd = 0;
	numNormPromoted = 0;
	VIP_WT = 0;
	RstPrd = 0;
	AutoPromotionLimit = 0;
	BO = 0;
	InjProp = 0;
	NumberOfEvents = 0;
	/*BO = 0;
	BN = 0;
	BG = 0;
	BV = 0;*/
	//*****************************	
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
	{
		SimulationFunction(1);
		break;
	}
	case MODE_STEP:
	{
		SimulationFunction(2);
		break;
	}
	case MODE_SLNT:
	{
		SimulationFunction(3);
		break;
	}
	};
}
//*****************************************************************************
//This function load all the data from the input file and create the data of all cooks and events
void Restaurant::FileLoadingFunction()
{
	//string filename;
	pGUI->PrintMessage("Enter File Name...");
	filename = pGUI->GetString();
	ifstream LoadFile;
	LoadFile.open(filename);
	if (!LoadFile.is_open())
	{
		pGUI->PrintMessage("Error loading the file...Click to continue..");
		pGUI->waitForClick();
		exit(0);
	}
	LoadFile >> numNormalCooks;
	LoadFile >> numVeganCooks;
	LoadFile >> numVIPCooks;
	int SN_min, SN_max, SG_min, SG_max, SV_min, SV_max;

	LoadFile >> SN_min >> SN_max >> SG_min >> SG_max >> SV_min >> SV_max;
	//int BO;
	LoadFile >> BO;
	int BN_min, BN_max, BG_min, BG_max, BV_min, BV_max;
	//int BN;
	LoadFile >> BN_min >> BN_max >> BG_min >> BG_max >> BV_min >> BV_max;
	//int BG;
	//int BV;
	Cook* pCook;
	int diffID = 1;
	int speed;
	int Break;
	srand((unsigned int)time(0));
	for (int i = 0; i < numNormalCooks; i++)
		//****************************************************
		//----------------------------------------------------
		//++++++++++++++++++++++++++++++++++++++++++++++++++++
		//TODO MISSING
	{//srand()
		speed = rand() % (SN_max - SN_min + 1) + SN_min;
		Break = rand() % (BN_max - BN_min + 1) + BN_min;
		pCook = new Cook(TYPE_NRM, speed, Break, diffID);
		NormalLinkedList.InsertEnd(pCook);
		diffID++;
	}
	for (int i = 0; i < numVeganCooks; i++)
	{
		speed = rand() % (SG_max - SG_min + 1) + SG_min;
		Break = rand() % (BG_max - BG_min + 1) + BG_min;
		pCook = new Cook(TYPE_VGAN, speed, Break, diffID);
		VeganLinkedList.InsertEnd(pCook);
		diffID++;
	}
	for (int i = 0; i < numVIPCooks; i++)
	{
		speed = rand() % (SV_max - SV_min + 1) + SV_min;
		Break = rand() % (BV_max - BV_min + 1) + BV_min;
		pCook = new Cook(TYPE_VIP, speed, Break, diffID);
		VIPLinkedList.InsertEnd(pCook);
		diffID++;
	}
	//int InjProp, RstPrd;
	LoadFile >> InjProp >> RstPrd;
	//int VIP_WT;
	LoadFile >> AutoPromotionLimit >> VIP_WT;
	LoadFile >> NumberOfEvents;
	for (int i = 0; i < NumberOfEvents; i++)
	{
		Event* pEvent;
		char Event_Type;
		LoadFile >> Event_Type;
		switch (Event_Type)
		{
		case 'R':
		{
			char Order_Type;
			LoadFile >> Order_Type;
			int Event_Time;
			LoadFile >> Event_Time;
			int Order_ID;
			LoadFile >> Order_ID;
			//OrderID = Order_ID;
			int Size;
			LoadFile >> Size;
			int Money;
			LoadFile >> Money;
			switch (Order_Type)
			{
			case 'N':
			{
				pEvent = new ArrivalEvent(Event_Time, Order_ID, TYPE_NRM, Size, Money);
				EventsQueue.enqueue(pEvent);
				break;
			}
			case 'V':
			{
				pEvent = new ArrivalEvent(Event_Time, Order_ID, TYPE_VIP, Size, Money);
				EventsQueue.enqueue(pEvent);
				break;
			}
			case 'G':
			{
				pEvent = new ArrivalEvent(Event_Time, Order_ID, TYPE_VGAN, Size, Money);
				EventsQueue.enqueue(pEvent);
				break;
			}
			}
			break;
		}
		case 'X':
		{
			int Time_Step;
			LoadFile >> Time_Step;
			int Order_ID;
			LoadFile >> Order_ID;
			pEvent = new CancellationEvent(Time_Step, Order_ID);
			EventsQueue.enqueue(pEvent);
			break;
		}
		case 'P':
		{
			int Time_Step;
			LoadFile >> Time_Step;
			int Order_ID;
			LoadFile >> Order_ID;
			double EXMoney;
			LoadFile >> EXMoney;
			pEvent = new PromotionEvent(Time_Step, Order_ID, EXMoney);
			EventsQueue.enqueue(pEvent);
			break;
		}
		}
	}
}


////////*****************************************************************************************
//*******************
//This Function simulate the interactive mode and everything of phase 1
//This function deals with the GUI as it calls FillDrwaingList
//it calls FileLoadingFunction and Done Orders
void Restaurant::SimulationFunction(int x)
{
	this->FileLoadingFunction();
	string OutputFile;
	OutputFile = ("Out_" + filename);
	//OutputFile = OutputFile + ".txt";
	ofstream Save(OutputFile);
	Save << "FT\tID\tAT\tWT\tST" << endl;
	string ts = to_string(timestep);
	//int timestep = 0;
	if (x == 1 || x == 2)
	{
		pGUI->PrintMessage("Time Step = " + ts + " " + "WAIT FOR MOUSE CLICK");
		if (x == 1)
			pGUI->waitForClick();
		else if (x == 2)
			Sleep(1000);
		pGUI->UpdateInterface();
	}
	while (!EventsQueue.isEmpty() || !NormalOrders.isEmpty() || !VeganOrders.isEmpty() || !VIPOrders.IsEmpty() || !InServiceList.isEmpty())
	{
		timestep++;
		messageID = " ";
		ts = to_string(timestep);
		if (x == 1 || x == 2)
			pGUI->PrintMessage("Time Step = " + ts + " " + "WAIT FOR MOUSE CLICK");
		this->ExecuteEvents(timestep);
		//if ((timestep % 5) == 0)  //hannah
		this->AutoPromotion();
		this->DoneOrders();
		//this->InABreak(timestep);
		this->FinishBreak(timestep);
		this->AssignOrder();
		this->InjuredCook(timestep);
		
		if (x == 1 || x == 2)
		{
			this->FillDrawingList();
			int total_ServindOrders = numServNormalOrd + numServVeganOrd + numServVIPOrd;
			pGUI->PrintMessage("Available Cooks: N" + to_string(numNormalCooks) + "  G" + to_string(numVeganCooks) + "  V" + to_string(numVIPCooks), 1);
			pGUI->PrintMessage("Number of waiting orders " + to_string(total_waitingOrders) + " : " + "N" + to_string(numWaitingNormalOrd) + " G" + to_string(numWaitingVeganOrd) + " V" + to_string(numWaitingVIPOrd), 2);
			pGUI->PrintMessage("Number of Serving orders " + to_string(total_ServindOrders) + " : " + "N" + to_string(numServNormalOrd) + " G" + to_string(numServVeganOrd) + " V" + to_string(numServVIPOrd), 3);
			pGUI->PrintMessage(messageID, 4);
			pGUI->UpdateInterface();
			if (x == 1)
				pGUI->waitForClick();
			else if (x == 2)
				Sleep(1000);
		}
		/*numWaitingVeganOrd = 0;
		numWaitingVIPOrd = 0;
		numWaitingNormalOrd = 0;*/
	}
	int total_ServindOrders = numServNormalOrd + numServVeganOrd + numServVIPOrd;
	this->EndCooksBreak();
	
	if (x == 1 || x == 2)
	{
		this->FillDrawingList();
		pGUI->PrintMessage("Available Cooks: N" + to_string(numNormalCooks) + "  G" + to_string(numVeganCooks) + "  V" + to_string(numVIPCooks), 1);
		pGUI->PrintMessage("Number of waiting orders " + to_string(total_waitingOrders) + " : " + "N" + to_string(numWaitingNormalOrd) + " G" + to_string(numWaitingVeganOrd) + " V" + to_string(numWaitingVIPOrd), 2);
		pGUI->PrintMessage("Number of Serving orders " + to_string(total_ServindOrders) + " : " + "N" + to_string(numServNormalOrd) + " G" + to_string(numServVeganOrd) + " V" + to_string(numServVIPOrd), 3);	pGUI->UpdateInterface();
		Sleep(1000);
		pGUI->PrintMessage("Finished... Click to continue..");
		pGUI->UpdateInterface();
		pGUI->waitForClick();
	}
	int size = 0;
	this->SortDoneOrders();
	Order** DoneArr = DoneList.toArray(size);
	int* arrWait = new int[size];
	int* arrServ = new int[size];
	for (int i = 0; i < size; i++)
	{
		arrWait[i] = DoneArr[i]->getWaitingTime();
		arrServ[i] = DoneArr[i]->getServiceTime();
		Order* pOrd = DoneArr[i];
		Save << pOrd->getFinishTime() << "\t" << pOrd->GetID() << "\t" << pOrd->getArrivalTime() << "\t" << pOrd->getWaitingTime() << "\t" << pOrd->getServiceTime() << endl;
	}
	double AvgWait = this->CalcAVG(arrWait, size);
	double AvgServ = this->CalcAVG(arrServ, size);
	int numOrders = numDoneNormOrd + numDoneVeganOrd + numDoneVIPOrd;
	Save << "Orders: " << numOrders << " [Norm: " << numDoneNormOrd << ", Veg: " << numDoneVeganOrd << ", VIP: " << numDoneVIPOrd << "]" << endl;
	int numCooks = numNormalCooks + numVeganCooks + numVIPCooks;
	Save << "cooks: " << numCooks << " [Norm: " << numNormalCooks << ", Veg: " << numVeganCooks << ", VIP: " << numVIPCooks << ", injured: " << numINJCooks << "]" << endl;
	Save << "Avg Wait = " << AvgWait << ", Avg Serv = " << AvgServ << endl;
	//the autopromoted percentage is calculate by dividing the number of autopromoted orders over the total number of autopromoted orders + Normal orders promation + Done Normal Order
	double AutopromotedPercentage;
	if (numAutoPromoted == 0 || (numAutoPromoted == 0 && numNormPromoted == 0 && numDoneNormOrd == 0))
		AutopromotedPercentage = 0;
	else
		AutopromotedPercentage = (numAutoPromoted / ((double)numAutoPromoted + (double)numDoneNormOrd + (double)numNormPromoted)) * 100;
	Save << "Urgent Orders: " << numUrgentOrd << ", Auto - promoted: " << AutopromotedPercentage << "%" << endl;
	if (x == 3)
	{
		pGUI->PrintMessage("Output File Saved Successfully with name ("+OutputFile+")");
		pGUI->PrintMessage("Click To Continue...", 1);
		pGUI->UpdateInterface();
		pGUI->waitForClick();
	}
}
double Restaurant::CalcAVG(int* arr, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum = sum + arr[i];
	}
	double AVG;
	if (sum == 0 || size == 0)
		AVG = 0;
	else
		AVG = sum / (double)size;
	return AVG;
}
//*********************
///////*****************************************************************************************


//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

//*******************************************************************

//*******************************************************************

Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	pGUI->ResetDrawingList();
	int size = 0;
	//******************************************************//Draw the Normal Cooks
	Cook** Normal_Array = NormalLinkedList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Cook* pCook = Normal_Array[i];
		pGUI->AddToDrawingList(pCook);
	}
	//Draw the Vegan Cooks
	Cook** Vegan_Array = VeganLinkedList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Cook* pCook = Vegan_Array[i];
		pGUI->AddToDrawingList(pCook);
	}
	//Draw the VIP Cooks
	Cook** VIP_Array = VIPLinkedList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Cook* pCook = VIP_Array[i];
		pGUI->AddToDrawingList(pCook);
	}
	//*******************************************************************************
	//Draw the VIP Orders the Vegan orders then Normal Orders in the waiting orders corner
	//this->DistributeOrders();
	//this->getOrderQueue();
	//this->InsertService();
	//OrderQueue.SortOrdersByArrivalTime(OrderQueue);
	Order** UrgentArr = urgentOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Order* pOrd = UrgentArr[i];   //Hal el order tyoe heya el msh btkhaleh yetresm?
		pGUI->AddToDrawingList(pOrd);
	}
	Order** VIPOrders_Array = VIPOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Order* pOrd = VIPOrders_Array[i];
		pGUI->AddToDrawingList(pOrd);
	}
	Order** VeganOrders_Array = VeganOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Order* pOrd = VeganOrders_Array[i];
		pGUI->AddToDrawingList(pOrd);
	}
	Order** NormalOrders_Array = NormalOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Order* pOrd = NormalOrders_Array[i];
		pGUI->AddToDrawingList(pOrd);
	}
	//**************************************************** Drawing InService
	Order** InServiceArr = InServiceList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Order* pOrd = InServiceArr[i];
		pGUI->AddToDrawingList(pOrd);
	}
	//*****************************************************Drawing DoneOrders
	Order** DoneArr = DoneList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		Order* pOrd = DoneArr[i];
		pGUI->AddToDrawingList(pOrd);
	}
	//***************************************************************
}
//*********************************************************************
//This function add the orders into queues according to their type 
//All VIP orders are in priorty queue and All Vegan Orders are in another queue and All Normal Orders are in another queue
void Restaurant::AddtoOrderQueue(Order* pOrd)
{
	total_waitingOrders++;
	switch (pOrd->GetType())
	{
	case(TYPE_NRM):
	{
		NormalOrders.InsertEnd(pOrd);
		numWaitingNormalOrd++;
		break;
	}
	case(TYPE_VGAN):
	{
		VeganOrders.enqueue(pOrd);
		numWaitingVeganOrd++;
		break;
	}
	case(TYPE_VIP):
	{
		VIPOrders.EnqueueSorted(pOrd);
		numWaitingVIPOrd++;
		break;
	}
	};
}
//This Function takes an Order ID and find the corresponding pointer and it checks that this id is for a Normal Order and then return the pointer
Order* Restaurant::FindID(int ID)
{
	int size = 0;
	Order** Arr = NormalOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		if (Arr[i]->GetID() == ID && Arr[i]->GetType() == TYPE_NRM)
		{
			return Arr[i];
		}
	}
	return nullptr;
}
//This function take an order pointer and delete this order from the OrderQueue
//This function calls function CancelItem in Queue to cancel this order and then decrement the number of total waiting orders
void Restaurant::CancelOrder(Order* pOrd)
{
	NormalOrders.DeleteNode(pOrd);
	total_waitingOrders--;
	numWaitingNormalOrd--;
}
void Restaurant::Promote(Order* pOrd)
{
	VIPOrders.EnqueueSorted(pOrd);
	NormalOrders.DeleteNode(pOrd);
	numWaitingVIPOrd++;
	numWaitingNormalOrd--;
	numNormPromoted++;
}
void Restaurant::AutoPromotion()
{
	Order* pOrd = nullptr;
	//Queue<Order*>temp;
	if (!NormalOrders.isEmpty())
		pOrd = NormalOrders.getHeadItem();
	while (pOrd)
	{
		Order* temp = pOrd;
		if (pOrd->GetType() == TYPE_NRM && timestep == AutoPromotionLimit + pOrd->getArrivalTime())
		{
			pOrd->SetType(TYPE_VIP);
			pOrd = NormalOrders.GetNext(pOrd);
			this->Promote(temp);//increment number of VIP orders and decrement the normal Orders
			numAutoPromoted++;
			//this->DistributeOrders();
			//this->getOrderQueue();
		}
		else
		{
			pOrd = NormalOrders.GetNext(pOrd);
		}
	}

}
//*********************************************************************
/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////
//**********************************************************************************************************
//This function moves Orders from Normal list and Vegan queue and VIP PriorityQueue to InServiceList to be displayed in the Serving corner
//This function set the status of the order to serving and set the service and finish time of the order
void Restaurant::InsertService(Order* pOrd, Cook* pCook)
{
	if (pOrd->GetType() == TYPE_NRM)
	{
		pOrd->setpCook(pCook); //remove
		pCook->setpOrder(pOrd);
		//pOrd->setCookID(pCook->GetID());
		pOrd->setStatus(SRV);
		pOrd->setStartService(timestep);
		pOrd->setFinishTime((int)(timestep + ceil (pOrd->getOrderSize()/(double)pCook->GetSpeed())));
		pOrd->setServiceTime((pOrd->getFinishTime()-pOrd->getStartService()));
		pOrd->setWaitingTime((pOrd->getStartService() - pOrd->getArrivalTime()));
		InServiceList.InsertEnd(pOrd);
		//NormalOrders.DeleteFirst();
		//NormalOrders.dequeue(pOrd);
		total_waitingOrders--;    // decrementing the number of waiting order
		numWaitingNormalOrd--;             // decrementing the number of normal order
		numServNormalOrd++;
	}
	else if (pOrd->GetType() == TYPE_VGAN)
	{
		pOrd->setpCook(pCook); //remove
		pCook->setpOrder(pOrd);
		pOrd->setStatus(SRV);
		pOrd->setStartService(timestep);
		pOrd->setFinishTime((int)(timestep + ceil(pOrd->getOrderSize() / (double)pCook->GetSpeed())));
		pOrd->setServiceTime((pOrd->getFinishTime() - pOrd->getStartService()));
		pOrd->setWaitingTime((pOrd->getStartService() - pOrd->getArrivalTime()));
		InServiceList.InsertEnd(pOrd);
		total_waitingOrders--;         // decrementing the number of waiting order
		numWaitingVeganOrd--;                 // decrementing the number of vegan order
		numServVeganOrd++;
	}
	else if (pOrd->GetType() == TYPE_VIP)
	{
		pOrd->setpCook(pCook); //remove
		pCook->setpOrder(pOrd);
		pOrd->setStatus(SRV);
		pOrd->setStartService(timestep);
		pOrd->setFinishTime((int)(timestep + ceil(pOrd->getOrderSize() / (double)pCook->GetSpeed())));
		pOrd->setServiceTime((pOrd->getFinishTime() - pOrd->getStartService()));
		pOrd->setWaitingTime((pOrd->getStartService() - pOrd->getArrivalTime()));
		InServiceList.InsertEnd(pOrd);
		total_waitingOrders--;            // decrementing the number of waiting order
		numWaitingVIPOrd--;                       // decrementing the number of VIP order
		numServVIPOrd++;
	}
	else if (pOrd->GetType() == TYPE_URG_VIP)  //changed
	{
		pOrd->setpCook(pCook); //remove
		pCook->setpOrder(pOrd);
		pOrd->setStatus(SRV);
		pOrd->setStartService(timestep);
		pOrd->setFinishTime(timestep + pCook->GetSpeed());
		pOrd->setServiceTime((pOrd->getFinishTime() - pOrd->getStartService()));
		pOrd->setWaitingTime((pOrd->getStartService() - pOrd->getArrivalTime()));
		InServiceList.InsertEnd(pOrd);
		total_waitingOrders--;
		numWaitingVIPOrd--; 
		numServVIPOrd++;
	}
}//end of Inservice

//*************************
//This function move Orders from InServiceList to DoneList to be displayed in the Done corner
void Restaurant::DoneOrders()
{
	Order* pOrd = nullptr;
	if (!InServiceList.isEmpty())
		pOrd = InServiceList.getHeadItem();
	while (pOrd)
	{
		Order* temp = pOrd;
		if (pOrd->getFinishTime() == timestep)
		{
			if (pOrd->GetType() == TYPE_NRM)
			{
				//pOrd->setCookID(0);
				this->FinishedCooks(pOrd->getpCook());
				pOrd->setStatus(DONE);              //To be able to draw the order in Done region we have to change it's status fist
				DoneList.InsertEnd(pOrd);
				pOrd = InServiceList.GetNext(pOrd);
				InServiceList.DeleteNode(temp);
				numDoneNormOrd++;
				numServNormalOrd--;
			}
			else if (pOrd->GetType() == TYPE_VGAN)
			{
				//pOrd->setCookID(0); //remove
				this->FinishedCooks(pOrd->getpCook());
				pOrd->setStatus(DONE);
				DoneList.InsertEnd(pOrd);
				pOrd = InServiceList.GetNext(pOrd);
				InServiceList.DeleteNode(temp);
				numDoneVeganOrd++;
				numServVeganOrd--;
			}
			else if (pOrd->GetType() == TYPE_VIP)
			{
				//pOrd->setCookID(0);
				this->FinishedCooks(pOrd->getpCook());
				pOrd->setStatus(DONE);
				DoneList.InsertEnd(pOrd);
				pOrd = InServiceList.GetNext(pOrd);
				InServiceList.DeleteNode(temp);
				numDoneVIPOrd++;
				numServVIPOrd--;
			}
			else if (pOrd->GetType() == TYPE_URG_VIP)
			{
				//pOrd->setCookID(0);
				this->FinishedCooks(pOrd->getpCook());
				pOrd->setStatus(DONE);
				DoneList.InsertEnd(pOrd);
				pOrd = InServiceList.GetNext(pOrd);
				InServiceList.DeleteNode(temp);
				numDoneVIPOrd++;
				numUrgentOrd++;
				numServVIPOrd--;
			}
		}
		else
		{
			pOrd = InServiceList.GetNext(pOrd);
		}
	}
}
//This function assign waiting orders to available cooks if there are available cooks
void Restaurant::AssignOrder()
{
	Order* pOrd;
	Queue<Order*> tempVIP;
	while (!VIPOrders.IsEmpty())
	{
		VIPOrders.Peek(pOrd);
		if ((timestep - pOrd->getArrivalTime()) >= VIP_WT) //changed
		{
			urgentOrders.InsertEnd(pOrd);
			VIPOrders.DequeueSorted(pOrd);
			pOrd->SetType(TYPE_URG_VIP);
		}
		else
		{
			tempVIP.enqueue(pOrd);
			VIPOrders.DequeueSorted(pOrd);
		}
	}
	while (!tempVIP.isEmpty())
	{
		tempVIP.dequeue(pOrd);
		VIPOrders.EnqueueSorted(pOrd);
	}
	while (!urgentOrders.isEmpty())
	{
		pOrd = urgentOrders.getHeadItem();
		bool isAssigned = this->AssignCook(pOrd);
		if (isAssigned)
		{
			//pOrd->setServiceTime(timestep);
			urgentOrders.DeleteFirst();
			this->msgIDFunction(pOrd);
		}
		else
			break;
	}
	while (!VIPOrders.IsEmpty())
	{
		VIPOrders.Peek(pOrd);
		bool isAssigned = this->AssignCook(pOrd);
		if (isAssigned)
		{
			VIPOrders.DequeueSorted(pOrd);
			this->msgIDFunction(pOrd);
		}
		else
		{
			break;
		}
	}
	while (!VeganOrders.isEmpty())
	{
		VeganOrders.peekFront(pOrd);
		bool isAssigned = this->AssignCook(pOrd);
		if (isAssigned)
		{
			VeganOrders.dequeue(pOrd);
			this->msgIDFunction(pOrd);

		}
		else
		{
			break;
		}
	}
	while (!NormalOrders.isEmpty())
	{
		pOrd = NormalOrders.getHeadItem();
		bool isAssigned = this->AssignCook(pOrd);
		if (isAssigned)
		{
			NormalOrders.DeleteFirst();
			this->msgIDFunction(pOrd);

		}
		else
		{
			break;
		}
	}
}
//This function takes a pointer to an order and checks if there is an available cook or not
//if there is an available cook this function assign the order to the available cooks and return true. if there are no available cooks it returns false 
bool Restaurant::AssignCook(Order* pOrd)
{
	Cook* pCook = nullptr;
	if (pOrd->GetType() == TYPE_URG_VIP)
	{
		if (!VIPLinkedList.isEmpty())
		{
			pCook = VIPLinkedList.getHeadItem();
			VIPLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingVIPOrd++;
			numVIPCooks--;
			return true;
		}
		else if (!NormalLinkedList.isEmpty())
		{
			pCook = NormalLinkedList.getHeadItem();
			NormalLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingVIPOrd++;
			numNormalCooks--;
			return true;
		}
		else if (!VeganLinkedList.isEmpty())
		{
			pCook = VeganLinkedList.getHeadItem();
			VeganLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingVIPOrd++;
			numVeganCooks--;
			return true;
		}

		else if (!BreakCooks.isEmpty())
		{
			pCook = BreakCooks.getHeadItem();
		//	Cook* temp = pCook;
			while (pCook)
			{
				if (pCook->getCookStatus() == INJ || pCook->getCookStatus() == BREAK)
				{
					BusyCooks.InsertEnd(pCook);
					BreakCooks.DeleteNode(pCook);
					InsertService(pOrd, pCook);
					pCook->setPausedBreak(timestep);
					if (pCook->getCookStatus() == INJ)
						pCook->setCookStatus(Broken_RestPeriod);
					else if (pCook->getCookStatus() == BREAK)
						pCook->setCookStatus(Broken_Break);
					return true;
				}
				else
					pCook = BreakCooks.GetNext(pCook);
			}
			pCook = BreakCooks.getHeadItem();
			if (pCook->getCookStatus() == Broken_Break || pCook->getCookStatus() == Broken_RestPeriod)
			{
				BusyCooks.InsertEnd(pCook);
				BreakCooks.DeleteFirst();
				InsertService(pOrd, pCook);
				pCook->setPausedBreak(timestep);
				return true;
			}
		}
		else
		{
			return false;
		}
	}//end if Urgent
	if (pOrd->GetType() == TYPE_VIP)
	{
		if (!VIPLinkedList.isEmpty())
		{
			pCook = VIPLinkedList.getHeadItem();
			VIPLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingVIPOrd++;
			numVIPCooks--;                // decrementing the number of VIP cooks
			return true;
		}
		else if (!NormalLinkedList.isEmpty())
		{
			pCook = NormalLinkedList.getHeadItem();
			NormalLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingVIPOrd++;
			numNormalCooks--;          // decrementing the number of Normal cooks
			return true;
		}
		else if (!VeganLinkedList.isEmpty())
		{
			pCook = VeganLinkedList.getHeadItem();
			VeganLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingVIPOrd++;
			numVeganCooks--;            // decrementing the number of Vegan cooks
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (pOrd->GetType() == TYPE_VGAN)
	{
		if (!VeganLinkedList.isEmpty())
		{
			pCook = VeganLinkedList.getHeadItem();
			VeganLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingVeganOrd++;
			numVeganCooks--;            // decrementing the number of Vegan cooks
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (pOrd->GetType() == TYPE_NRM)
	{
		if (!NormalLinkedList.isEmpty())
		{
			pCook = NormalLinkedList.getHeadItem();
			NormalLinkedList.DeleteFirst();
			pCook->setCookStatus(BUSY);
			BusyCooks.InsertEnd(pCook);
			InsertService(pOrd, pCook);
			//numWaitingNormalOrd++;
			numNormalCooks--;                // decrementing the number of Normal cooks
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
// This function takes the cook ID to remove him from the busy cooks
//It gives the cook a break if he finished the number of orders to be done before taking a break
// If the cook doesn't finish this number of orders he will be available again in the available cooks
void Restaurant::FinishedCooks(Cook* pCook)
{
	BusyCooks.DeleteNode(pCook);
	pCook->setnumDoneOrders((pCook->GetnumDoneOrders() + 1));
	if (pCook->getCookStatus() == INJ)
	{
		this->InABreak(pCook);
	}
	else if (pCook->getCookStatus() == Broken_Break || pCook->getCookStatus() == Broken_RestPeriod)   //Changed
	{
		this->InABreak(pCook);
		/*BreakCooks.InsertEnd(pCook);
		pCook->setResumedBreak(timestep); // Q: howa 3ade lw khadt el timestep el heya data memeber? kda msh hatsbeb ay lagging fl current timestep el bnkoon feha fl run???
		pCook->setBrokenBreakDuration(pCook->getBrokenBreakDuration() + ( pCook->getResumedBreak()-pCook->getPausedBreak() ));
	*/
	}//28-5
	else if (pCook->GetType() == TYPE_NRM)
	{
		if (pCook->GetnumDoneOrders() >= BO)
			this->InABreak(pCook);
		else
		{
			pCook->setCookStatus(AVB);
			pCook->setpOrder(nullptr);
			NormalLinkedList.InsertEnd(pCook);
			numNormalCooks++;
		}
	}
	else if (pCook->GetType() == TYPE_VGAN)
	{
		if (pCook->GetnumDoneOrders() >= BO)
			this->InABreak(pCook);
		else
		{
			pCook->setCookStatus(AVB);
			pCook->setpOrder(nullptr);
			VeganLinkedList.InsertEnd(pCook);
			numVeganCooks++;
		}
	}
	else if (pCook->GetType() == TYPE_VIP)
	{
		if (pCook->GetnumDoneOrders() >= BO)
			this->InABreak(pCook);
		else
		{
			pCook->setCookStatus(AVB);
			pCook->setpOrder(nullptr);
			VIPLinkedList.InsertEnd(pCook);
			numVIPCooks++;
		}
	}
}
//This function takes a pointer to the cook that should takes a break 
//It changes the status of the cook to break and put the cook in a break
void Restaurant::InABreak(Cook* pCook)
{
	if (pCook->getCookStatus() == BUSY)
	{
		pCook->setnumDoneOrders((pCook->GetnumDoneOrders() - BO));
		pCook->setCookStatus(BREAK);
		pCook->setStartBreak(timestep);
		pCook->setEndBreak(pCook->GetStartBreak() + pCook->GetBreak());
		BreakCooks.InsertEnd(pCook);
	}
	else if (pCook->getCookStatus() == INJ)
	{
		//pCook->setCookStatus(BREAK);
		pCook->setStartBreak(timestep);
		pCook->setEndBreak(pCook->GetStartBreak() + RstPrd);
		BreakCooks.InsertEnd(pCook);
	}
	else if (pCook->getCookStatus()==Broken_Break || pCook->getCookStatus()==Broken_RestPeriod)
	{
		pCook->setResumedBreak(timestep);
		if (pCook->GetnumDoneOrders() >= BO)
		{
			pCook->setnumDoneOrders((pCook->GetnumDoneOrders() - BO));
			pCook->setEndBreak((pCook->getEndBreak() + (pCook->getResumedBreak() - pCook->getPausedBreak()) + pCook->GetBreak()));
		}
		else
			pCook->setEndBreak((pCook->getEndBreak() + (pCook->getResumedBreak() - pCook->getPausedBreak())));
		BreakCooks.InsertEnd(pCook);	
	}
}

void Restaurant::FinishBreak(int time)
{
	Cook* pCook = nullptr;
	if (!BreakCooks.isEmpty())
		pCook = BreakCooks.getHeadItem();
	while (pCook)
	{
		Cook* temp = pCook;
		if (pCook->getCookStatus() == Broken_Break || pCook->getCookStatus() == Broken_RestPeriod)
		{
			if (pCook->getEndBreak() == timestep)
			{
				pCook->setCookStatus(AVB);
				pCook->setEndBreak(0);
				pCook->setPausedBreak(0);
				pCook->setResumedBreak(0);
				pCook->setStartBreak(0);
				pCook->setpOrder(nullptr);
				if (pCook->GetType() == TYPE_VIP)
				{
					VIPLinkedList.InsertEnd(pCook);  numVIPCooks++;
				}

				else if (pCook->GetType() == TYPE_VGAN)
				{
					VeganLinkedList.InsertEnd(pCook);  numVeganCooks++;
				}

				else if (pCook->GetType() == TYPE_NRM)
				{
					NormalLinkedList.InsertEnd(pCook);  numNormalCooks++;
				}
				pCook = BreakCooks.GetNext(pCook);
				BreakCooks.DeleteNode(temp);
			}
			else 
				pCook = BreakCooks.GetNext(pCook);

		}

		else if (pCook->getCookStatus() == BREAK && pCook->getEndBreak()==timestep)
		{
			pCook->setCookStatus(AVB);
			pCook->setEndBreak(0);
			pCook->setPausedBreak(0);
			pCook->setResumedBreak(0);
			pCook->setStartBreak(0);
			pCook->setpOrder(nullptr);
			if (pCook->GetType() == TYPE_NRM)
			{
				NormalLinkedList.InsertEnd(pCook);
				numNormalCooks++;
			}
			else if (pCook->GetType() == TYPE_VIP)
			{
				VIPLinkedList.InsertEnd(pCook);
				numVIPCooks++;

			}
			else if (pCook->GetType()==TYPE_VGAN)
			{
				VeganLinkedList.InsertEnd(pCook);
				numVeganCooks++;
			}
			pCook = BreakCooks.GetNext(pCook);
			BreakCooks.DeleteNode(temp);
		}
		else if (pCook->getCookStatus() == INJ && pCook->getEndBreak()==timestep)
		{
			pCook->setCookStatus(AVB);
			pCook->setEndBreak(0);
			pCook->setPausedBreak(0);
			pCook->setResumedBreak(0);
			pCook->setStartBreak(0);
			pCook->setpOrder(nullptr);
			pCook->setSpeed(pCook->getSpeedBeforeINJ());
			if (pCook->GetType() == TYPE_VIP)
			{
				VIPLinkedList.InsertEnd(pCook);
				numVIPCooks++;
			}
			else if (pCook->GetType() == TYPE_VGAN)
			{
				VeganLinkedList.InsertEnd(pCook);
				numVeganCooks++;
			}
			else if (pCook->GetType() == TYPE_NRM)
			{
				NormalLinkedList.InsertEnd(pCook);
				numNormalCooks++;
			}
			pCook = BreakCooks.GetNext(pCook);
			BreakCooks.DeleteNode(temp);
		}
		else
		{
			pCook = BreakCooks.GetNext(pCook);
		}
	}
}
//******************************//comment important
void Restaurant::InjuredCook(int timestep)
{
	Cook* pCook=nullptr;
	Order* pOrd=nullptr;
	double R;
	srand((unsigned int)time(0));
	R = (rand() % 100);
	R = R / 100;

	if (R <= InjProp)
	{
		if (!BusyCooks.isEmpty())
			pCook = BusyCooks.getHeadItem();
		while (pCook)
		{
			
			if (pCook->getCookStatus() == BUSY)
			{
				//BusyCooks.DeleteNode(pCook);
				//BusyCooks.InsertEnd(pCook);
				int speedBefore = pCook->GetSpeed();
				pCook->setSpeedBeforeINJ(pCook->GetSpeed());
				if (pCook->GetSpeed() != 1)
					pCook->setSpeed(pCook->GetSpeed() / 2);
				pCook->setCookStatus(INJ);
				pOrd = pCook->GetpOrder();
				pOrd->setFinishTime((int)(ceil((pOrd->getOrderSize() - (((double)timestep - pOrd->getStartService()) * speedBefore)) / (double)(pCook->GetSpeed()))) + timestep);
				pOrd->setServiceTime((pOrd->getFinishTime() - pOrd->getStartService()));
				numINJCooks++;
				return;
			}
			else
				pCook = BusyCooks.GetNext(pCook);
		}
	}
	else
		return;
}

void Restaurant::EndCooksBreak()
{
	Cook* pCook = nullptr;
	if (EventsQueue.isEmpty() && NormalOrders.isEmpty() && VeganOrders.isEmpty() && VIPOrders.IsEmpty() && InServiceList.isEmpty())
	{ 
		while (!BreakCooks.isEmpty())
		{
			pCook = BreakCooks.getHeadItem();
			BreakCooks.DeleteFirst();
			pCook->setCookStatus(AVB);
			if (pCook->GetType() == TYPE_VIP)
			{
				VIPLinkedList.InsertEnd(pCook);
				numVIPCooks++;
			}
			else if (pCook->GetType() == TYPE_VGAN)
			{
				VeganLinkedList.InsertEnd(pCook);
				numVeganCooks++;
			}
			else if (pCook->GetType() == TYPE_NRM)
			{
				NormalLinkedList.InsertEnd(pCook);
				numNormalCooks++;
			}
		}
	}

}
void Restaurant::SortDoneOrders()
{
	Order* pOrd = nullptr;
	Order* nextptr = nullptr;
	Order* minServTime = nullptr;
	Order* temp = nullptr;
	if (!DoneList.isEmpty())
	{
		pOrd = DoneList.getHeadItem();
		minServTime = pOrd;
		nextptr = DoneList.GetNext(pOrd);
	}
	while (nextptr)
	{
		if (pOrd->getFinishTime() == nextptr->getFinishTime())
		{
			while (nextptr)
			{
				if (nextptr->getFinishTime() != pOrd->getFinishTime())
					break;
				if (nextptr->getServiceTime() <= minServTime->getServiceTime())
				{
					minServTime = nextptr;
					nextptr = DoneList.GetNext(nextptr);
				}
				else
					nextptr = DoneList.GetNext(nextptr);
			}
			if (minServTime != pOrd)
			{
				temp = minServTime;
				DoneList.DeleteNode(minServTime);
				DoneList.InsertNode(minServTime, pOrd);
			}
			if (minServTime->getServiceTime() > pOrd->getServiceTime() || minServTime == pOrd)
			{
				pOrd = DoneList.GetNext(pOrd);
				minServTime = pOrd;
				nextptr = DoneList.GetNext(pOrd);
			}
			else
			{

				nextptr = DoneList.GetNext(pOrd);
				if (nextptr == nullptr)
				{
					pOrd = minServTime;
				}
				minServTime = pOrd;
			}
			if (pOrd->getFinishTime() != nextptr->getFinishTime())
			{
				pOrd = DoneList.GetNext(pOrd);
				minServTime = pOrd;
				nextptr = DoneList.GetNext(pOrd);
			}

		}
		else
		{
			pOrd = DoneList.GetNext(pOrd);
			minServTime = pOrd;
			nextptr = DoneList.GetNext(pOrd);
		}

	}
}
void Restaurant::msgIDFunction(Order* pOrd)
{
	Cook* pCook = pOrd->getpCook();
	int cookId = pCook->GetID();
	int ordId = pOrd->GetID();

	if (pCook->GetType() == TYPE_NRM)
	{
		messageID += " N";
		messageID += to_string(cookId) + "(";

		if (pOrd->GetType() == TYPE_NRM)
		{
			messageID += "N" + to_string(ordId) + ") ";
		}

		else if (pOrd->GetType() == TYPE_VGAN)
		{
			messageID += "G" + to_string(ordId) + ") ";
		}

		else if (pOrd->GetType() == TYPE_VIP || pOrd->GetType() == TYPE_URG_VIP)
		{
			messageID += "V" + to_string(ordId) + ") ";
		}
	}

	if (pCook->GetType() == TYPE_VGAN)
	{
		messageID += " G";
		messageID += to_string(cookId) + "(";

		if (pOrd->GetType() == TYPE_NRM)
		{
			messageID += "N" + to_string(ordId) + ") ";
		}

		else if (pOrd->GetType() == TYPE_VGAN)
		{
			messageID += "G" + to_string(ordId) + ") ";
		}

		else if (pOrd->GetType() == TYPE_VIP || pOrd->GetType() == TYPE_URG_VIP)
		{
			messageID += "V" + to_string(ordId) + ") ";
		}
	}

	if (pCook->GetType() == TYPE_VIP)
	{
		messageID += " V";
		messageID += to_string(cookId) + "(";

		if (pOrd->GetType() == TYPE_NRM)
		{
			messageID += "N" + to_string(ordId) + ") ";
		}

		else if (pOrd->GetType() == TYPE_VGAN)
		{
			messageID += "G" + to_string(ordId) + ") ";
		}

		else if (pOrd->GetType() == TYPE_VIP || pOrd->GetType() == TYPE_URG_VIP)
		{
			messageID += "V" + to_string(ordId) + ") ";
		}
	}
}

//**********************************************************************************************************

