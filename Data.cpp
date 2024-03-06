#include "Data.hpp"

//Contructors
Data::Data()
{
	mRecord = 0;
	mID = 0;
	mFirstName = "n/a";
	mLastName = "n/a";
	mEmail = "n/a";
	mCredits = "AU";
	mProgram = "n/a";
	mStanding = "n/a";
	mAbsences = 0;
}

Data::Data(unsigned int& newRecord, unsigned int& newID, std::string& newFirst,
	std::string& newLast, std::string& newEmail, std::string& newCredits,
	std::string& newProgram, std::string& newStanding, unsigned int& newAbsences)
{
	if (newRecord < 1000)
	{
		mRecord = newRecord;
	}
	else
	{
		mRecord = 0;
	}
	if (newID < 1000000000)
	{
		mID = newID;
	}
	else
	{
		mID = 0;
	}
	mFirstName = newFirst;
	mLastName = newLast;
	mEmail = newEmail;
	mCredits = newCredits;
	mProgram = newProgram;
	mStanding = newStanding;
	mAbsences = newAbsences;
}

//Copy Constructor
Data::Data(Data& copyData)
{
	mRecord = copyData.mRecord;
	mID = copyData.mID;
	mFirstName = copyData.mFirstName;
	mLastName = copyData.mLastName;
	mEmail = copyData.mEmail;
	mCredits = copyData.mCredits;
	mProgram = copyData.mProgram;
	mStanding = copyData.mStanding;
	mAbsences = copyData.mAbsences;
	mStackDates = copyData.mStackDates;
}

//Destructor
Data::~Data()
{

}

//Copy assignment operator
Data& Data::operator= (Data& rhs)
{
	mRecord = rhs.mRecord;
	mID = rhs.mID;
	mFirstName = rhs.mFirstName;
	mLastName = rhs.mLastName;
	mEmail = rhs.mEmail;
	mCredits = rhs.mCredits;
	mProgram = rhs.mProgram;
	mStanding = rhs.mStanding;
	mAbsences = rhs.mAbsences;
	mStackDates = rhs.mStackDates;

	return *this;
}


//getters
//
unsigned int Data::getRecord()
{
	return mRecord;
}
unsigned int Data::getID()
{
	return mID;
}
std::string Data::getFirstName()
{
	return mFirstName;
}
std::string Data::getLastName()
{
	return mLastName;
}
std::string Data::getEmail()
{
	return mEmail;
}
std::string Data::getCredits()
{
	return mCredits;
}
std::string Data::getProgram()
{
	return mProgram;
}
std::string Data::getStanding()
{
	return mStanding;
}
unsigned int Data::getNumAbsences()
{
	return mAbsences;
}
std::string Data::getLastAbsence()
{
	return mStackDates.peek();
}
std::string Data::getAbsence(unsigned int index)
{
	return mStackDates.peekAt(index);
}

//setters
//
void Data::setRecord(const unsigned int& newRecord)
{
	if (newRecord < 1000)
	{
		mRecord = newRecord;
	}
}
void Data::setID(const unsigned int& newID)
{
	if (newID < 1000000000)
	{
		mID = newID;
	}
}
void Data::setFirstName(const std::string& newFirst)
{
	mFirstName = newFirst;
}
void Data::setLastName(const std::string& newLast)
{
	mLastName = newLast;
}
void Data::setEmail(const std::string& newEmail)
{
	mEmail = newEmail;
}
void Data::setCredits(const std::string& newCredits)
{
	mCredits = newCredits;
}
void Data::setProgram(const std::string& newProgram)
{
	mProgram = newProgram;
}
void Data::setStanding(const std::string& newStanding)
{
	mStanding = newStanding;
}
void Data::setAbsences(const unsigned int& newAbsences)
{
	mAbsences = newAbsences;
}

//member functions
void Data::addAbsence(const std::string& newAbsence)
{
	mStackDates.push(newAbsence);
	mAbsences++;
}
bool Data::removeAbsence(const std::string& removedAbsence)
{
	if (!mStackDates.isEmpty())
	{
		for (int index = 0; index < mStackDates.getSize(); index++)
		{
			if (removedAbsence == mStackDates.peekAt(index))
			{
				mStackDates.deleteAbsence(index);
				mAbsences--;
				return true;
			}
		}
	}

	return false;
}

