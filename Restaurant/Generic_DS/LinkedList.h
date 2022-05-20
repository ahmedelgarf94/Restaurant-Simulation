#ifndef _LINKEDLIST
#define _LINKEDLIST
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	/*void InsertEnd(const T &data)
	{
		/Node <T> p=Head;
		while (p)
		{
			if (p->getNext() ==NULL)
			{
			  Node<T> *k= new Node<T>(data);
			  k->setNext(NULL);
			  p->setNext(k);
			  break;
			}
			p= p->getNext();
		}



	}*/
	void InsertEnd(const T& data)
	{
		Node<T>* newPtr = new Node<T>(data);
		Node<T>* temp = Head;
		if (Head == nullptr)
		{
			Head = newPtr;
			Head->setNext(nullptr);
			return;
		}
		while (temp->getNext() != nullptr)
		{
			temp = temp->getNext();
		}
		temp->setNext(newPtr);
		newPtr->setNext(nullptr);
	}
	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key)
	{
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == Key)
			{
				return true;
			}
			p = p->getNext();
		}
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		Node<T>* p = Head;
		int c = 0;
		while (p)
		{
			if (p->getItem() == value)
				c++;
			p = p->getNext();
		}
		return c;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		Node<T>* p = Head;
		Head = Head->getNext();
		delete p;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* Q = Head;
		Node<T>* p = Head->getNext();
		while (Q)
		{
			if (p->getNext() == NULL)
			{
				Q->setNext(NULL);
				delete p;
				break;
			}
			Q = p;
			p = p->getNext();
		}
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)      // lw edetlo value doesn't exist fl list it crashes____ please fix this bug
	{
		Node<T>* Q = Head;
		Node<T>* p = Head->getNext();

		if (Head->getItem() == value)
		{
			DeleteFirst();
			return false;
		}


		while (Q)
		{
			if (p->getItem() == value)
			{
				Node<T>* s = p->getNext();
				Q->setNext(s);
				delete p;
				return true;
				break;
			}
			Q = p;
			p = p->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		Node<T>* Q = Head;
		Node<T>* p = Head->getNext();
		int c = 0;
		if (Head->getItem() == value)
		{
			DeleteFirst(); c++;
		}

		while (p)
		{
			while (p->getItem() == value)
			{
				Node<T>* s = p->getNext();
				Q->setNext(s);
				delete p;
				c++;
				p = s;

			}

			Q = p;
			p = p->getNext();
		}
		if (c > 0)
			return true;
		return false;
	}
	//******************************************************************************
	// new function convert linkedlist to array
	T* toArray(int& count)
	{
		count = 0;

		if (Head == nullptr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = Head;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = Head;
		for (int i = 0; i < count;i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	//how to use it
	/*cout << "Test to Array" << endl;
	int size = 0;
	L.toArray(size);
	int* Arr = new int[size];
	Arr = L.toArray(size);
	for (int i = 0; i < size; i++)
	{
		cout << Arr[i] << " ";
	}
	cout << endl;*/
	//***********************************************************************************
	bool isEmpty() const
	{
		if (Head == nullptr)
			return true;
		else
			return false;
	}
	void Merge(const LinkedList& L)
	{
		Node<T>* p = Head;
		while (p->getNext())
		{
			//if (p->getNext()== NULL )
			  //  break;
			p = p->getNext();
		}
		p->setNext(L.Head);
	}
	void sortCooksBy_ID(LinkedList<Cook*>& AvailableCooks)
	{
		Node<Cook*>* p = AvailableCooks.Head;
		Node<Cook*>* Q = p->getNext();
		Cook* temp;
		if (p == nullptr)
			return;

		int count = 0;
		while (p)
		{
			count++;
			p = p->getNext();
		}
		p = AvailableCooks.Head;
		for (int i = 0; i <= count; i++)
		{
			while (Q)
			{
				if ((p->getItem()->GetID()) > (Q->getItem()->GetID()))
				{
					temp = p->getItem();
					p->setItem(Q->getItem());
					Q->setItem(temp);
				}

				Q = Q->getNext();
			}//end of while

			p = p->getNext();
			if (p == nullptr)
				return;
			Q = p->getNext();
		}//end of forloop

	}//end of sorting
	T getHeadItem()
	{
		return Head->getItem();
	}
	T GetNext(T &ptr)
	{
		Node<T>* Moveptr = Head;
		while (Moveptr!=nullptr && Moveptr->getItem() != ptr)
			Moveptr = Moveptr->getNext();
		if (Moveptr!=nullptr && Moveptr->getNext() != nullptr)
			return Moveptr->getNext()->getItem();
		else
			return nullptr;


	}
	void Swap(const T& s)
	{
		Node<T>* p = Head;
		Node<T>* Q = p->getNext();
		Node<T>* tempItem = nullptr;

		if (p == nullptr)
			return;

		while (p)
		{
			if (p->getItem() == s)
			{
				tempItem = p;
				tempItem->setItem(p->getItem());
				p->setItem(Q->getItem());
				Q->setItem(tempItem->getItem());
				return;
			}

			else
			{
				p = Q;

				if (Q->getNext() == nullptr)
					return;
				else
					Q = Q->getNext();
			}
		}
	}
	void InsertNode(const T& value, const T& ref)
	{
		Node<T>* p = Head;
		if (Head == nullptr)
			return;

		if (ref == Head->getItem())
		{
			InsertBeg(value);
			return;
		}

		while (p->getNext())
		{
			if (p->getNext()->getItem() == ref)
			{
				Node<T>* addIt = new Node<T>(value);
				addIt->setNext(p->getNext());
				p->setNext(addIt);
				return;
			}

			else
			{
				p = p->getNext();
			}
		}



	}


};

#endif