#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "stack.hpp"

using std::cin;
using std::cout;
using std::endl;


class Data
{
public:
	//Contructor
	Data();

	Data(unsigned int& newRecord, unsigned int& newID, std::string& newFirst,
		std::string& newLast, std::string& newEmail, std::string& newCredits,
		std::string& newProgram, std::string& newStanding, unsigned int& newAbsences);

	//Copy Constructor
	Data(Data& copyData);

	//Destructor
	~Data();

	//Copy assignment operator
	Data& operator= (Data& rhs);

	//getters
	unsigned int getRecord();
	unsigned int getID();
	std::string getFirstName();
	std::string getLastName();
	std::string getEmail();
	std::string getCredits();
	std::string getProgram();
	std::string getStanding();
	unsigned int getNumAbsences();
	std::string getLastAbsence();
	std::string getAbsence(unsigned int index);

	//setters
	void setRecord(const unsigned int &newRecord);
	void setID(const unsigned int& newID);
	void setFirstName(const std::string &newFirst);
	void setLastName(const std::string& newLast);
	void setEmail(const std::string &newEmail);
	void setCredits(const std::string &newCredits);
	void setProgram(const std::string &newProgram);
	void setStanding(const std::string &newStanding);
	void setAbsences(const unsigned int& newAbsences);

	//member functions
	void addAbsence(const std::string& newAbsence);
	bool removeAbsence(const std::string& removedAbsence);



private:
	unsigned int mRecord;
	unsigned int mID;
	std::string mFirstName;
	std::string mLastName;
	std::string mEmail;
	std::string mCredits;
	std::string mProgram;
	std::string mStanding;
	unsigned int mAbsences;
	Stack mStackDates;
};