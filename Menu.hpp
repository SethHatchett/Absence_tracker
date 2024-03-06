#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "List.hpp"

using std::cin;
using std::cout;
using std::endl;

class Menu
{
public:
	//constructor
	Menu();

	//destructor
	~Menu();

	//menu functions
	void runSystem();

	unsigned int displayMenu();

	void pause();

	void importRecords();

	//helper function for importRecords()
	void insertNewAtFront(Data& newData);


	void markAbsences();

	//helper function for markAbsences()
	std::string getTime();


	void generateReport();

	//helper functions for generateReports()
	void printAll();

	void printThreshold(unsigned int numAbsences);


	//master list functions
	void storeMaster();

	void loadMaster();


	void editAbsence();


	void exitMenu();

private:
	List<Node<Data>>* mpStudentList;
};