#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Node.hpp"

using std::cin;
using std::cout;
using std::endl;

template <class T>
class List
{
public:
	//Constructor
	List();

	//Destructor
	~List();

	//Copy Constructor
	List(const List<T>& other);

	//Copy assignment operator
	List<T>& operator=(const List<T>& other);

	//getters
	T* getHeadPtr();

	//setters
	void setHeadPtr(T* newHead);

	//member functions
	T* createNewNode(Data& newData);


private:
	T* mpHead;
};

template<class T>
List<T>::List()
{
	mpHead = nullptr;
}

template<class T>
List<T>::~List()
{
	T* next = mpHead;
	T* curr = nullptr;
	while (next != nullptr)
	{
		curr = next;
		//set up for next node before pointer is deleted
		next = next->getNext();

		//delete curr node
		delete curr;
	}
}

template<class T>
List<T>::List(const List<T>& other)
{
	//check if empty list
	if (other.mpHead != nullptr)
	{
		//set deep copy of head ptr
		T* otherCurr = other.mpHead;
		mpHead = new T(otherCurr);
		T* newCurr = mpHead;

		//set to next node to prepare for while statement
		otherCurr = otherCurr->getNext();

		//deep copy until reaches end of "other" list
		while (otherCurr != nullptr)
		{
			newCurr->setNext(new T(otherCurr));
			otherCurr = otherCurr->getNext();
			newCurr = newCurr->getNext();
		}
	}
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other)
{
	//destroy current list
	while (mpHead != nullptr)
	{
		T* pNext = mpHead->getNext();
		delete mpHead;
		mpHead = pNext;
	}

	//check if "other" list is empty
	if (other.mpHead != nullptr)
	{
		//set deep copy of head ptr
		T* otherCurr = other.mpHead;
		mpHead = new T(otherCurr);
		T* newCurr = mpHead;

		//set to next node to prepare for while statement
		otherCurr = otherCurr->getNext();

		//deep copy until reaches end of "other" list
		while (otherCurr != nullptr)
		{
			newCurr->setNext(new T(otherCurr));
			otherCurr = otherCurr->getNext();
			newCurr = newCurr->getNext();
		}
	}

	return *this;
}

template<class T>
T* List<T>::getHeadPtr()
{
	return mpHead;
}

template<class T>
void List<T>::setHeadPtr(T* newHead)
{
	mpHead = newHead;
}

template<class T>
 T* List<T>::createNewNode(Data& newData)
{
	Data* pData = new Data(newData);
	T* newNode = new T(pData);
	return newNode;
}