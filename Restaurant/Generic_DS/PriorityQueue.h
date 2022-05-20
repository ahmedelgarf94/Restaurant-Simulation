#pragma once
#include <iostream>

#include "Node.h"

template <typename T>
class PriorityQueue
{
private:
	Node<T>* front;
public:


	PriorityQueue()
	{
		front = nullptr;
	}
/*
Function: IsEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
	bool IsEmpty()
	{
		if (front == nullptr)
			return true;
		else
			return false;
	}
	/*void EnqueueSorted(const T& data)
	{
		Node<T>* newNodeptr = new Node<T>(data);
		if (IsEmpty() || front->getItem() <= data)
		{
			newNodeptr->setNext(front);
			front = newNodeptr;
			return;
		}
		else
		{
			Node<T>* previous = front;
			Node<T>* next = front->getNext();
			while (next)
			{
				if (next->getItem() <= data)
				{
					previous->setNext(newNodeptr);
					newNodeptr->setNext(next);
					return;
				}
				previous = next;
				next = next->getNext();
			}
			previous->setNext(newNodeptr);
			newNodeptr->setNext(nullptr);
		}
	}*/

	/*Function:EnqueueSorted
Adds data to the queue depending on the priority of this data

Input: data .
Output: True if the operation is successful; otherwise false.
*/
	void EnqueueSorted( T& data)
	{
		Node<T>* newNodeptr = new Node<T>(data);
		double prData = data->Priority();
		if (IsEmpty() || front->getItem()->Priority() <= prData)
		{
			newNodeptr->setNext(front);
			front = newNodeptr;
			return;
		}
		else
		{

			Node<T>* previous = front;
			Node<T>* next = front->getNext();
			while (next)
			{
				if (next->getItem()->Priority() <= prData)
				{
					previous->setNext(newNodeptr);
					newNodeptr->setNext(next);
					return;
				}
				previous = next;
				next = next->getNext();
			}
			previous->setNext(newNodeptr);
			newNodeptr->setNext(nullptr);
		}
	}
	/*
Function: Peek
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
	bool Peek(T& data)
	{
		if (front == nullptr)
			return false;
		data = front->getItem();
		return true;
	}

	/*Function: DequeueSorted
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/
	bool DequeueSorted(T& data)
	{
		if (front == nullptr)
			return false;
		Node<T>* ptr = front;
		front = front->getNext();
		data = ptr->getItem();
		delete ptr;
		return true;
	}
	/*
	Function: RemoveItem
	Removes one of the intermediate items of the queue.

	Input: data
	Output: True if the operation is successful; otherwise false.
	*/
	bool RemoveItem(const T& data)
	{

		if (IsEmpty())
			return false;
		if (front->getItem() == data)
			return DequeueSorted(data);
		else
		{
			Node<T>* previous = front;
			Node<T>* next = front->getNext();
			while (next)
			{
				if (next->getItem() == data)
				{
					previous->setNext(next->getNext());
					delete next;
					next = nullptr;
					return true;
				}
				previous = next;
				next = next->getNext();
			}
		}
		return false;
	}

	/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/
	T* toArray(int& count)
	{
		count = 0;

		if (!front)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = front;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = front;
		for (int i = 0; i < count;i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	~PriorityQueue()
	{
	}

};


