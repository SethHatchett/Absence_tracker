#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Data.hpp"

using std::cin;
using std::cout;
using std::endl;

template <class T>
class Node
{
public:
	//Constructor
	Node(T* newData = nullptr);

	//Destructor
	~Node();

	//Copy Contructor
	Node(const Node<T>& copyNode);

	//Copy assignment operator
	Node<T>& operator= (Node<T>& rhs);

	//getters
	T* getData();
	Node<T>* getNext();

	//setters
	void setStudent(T* newStudent);
	void setNext(Node<T>* newNext);

	//member functions
	

private:
	T *mpStudent;
	Node<T>* mpNext;
};

//Constructor
template <class T>
Node<T>::Node(T* newData)
{
	mpStudent = newData;
	mpNext = nullptr;
}

//Destructor
template <class T>
Node<T>::~Node()
{
	delete mpStudent;
}

//Copy constructor
template<class T>
Node<T>::Node(const Node<T>& copyNode)
{
	mpStudent = new T(&*(copyNode->mpStudent));
	mpNext = nullptr;
}

//Copy assignment operator
template <class T>
Node<T>& Node<T>::operator= (Node<T>& rhs)
{
	*mpStudent = *(rhs->mpStudent);
	mpNext = nullptr;
}

//getters
template <class T>
T* Node<T>::getData()
{
	return mpStudent;
}

template <class T>
Node<T>* Node<T>::getNext()
{
	return mpNext;
}

//setters
template <class T>
void Node<T>::setStudent(T* newStudent)
{
	mpStudent = newStudent;
}

template <class T>
void Node<T>::setNext(Node<T>* newNext)
{
	mpNext = newNext;
}