#include "Menu.hpp"

Menu::Menu()
{
	mpStudentList = nullptr;
}

Menu::~Menu()
{
	delete mpStudentList;
}

void Menu::runSystem()
{
	//Starting screen
	cout << "Welcome to your personlized student absence manager!" << endl;

	cout << "Press any key to continue";
	cin.get();
	system("CLS");

	int selection = 0;
	
	//Display choices and execute based on selection
	do
	{
		selection = displayMenu();

		switch (selection)
		{
			//Import course list
		case 1:
			importRecords();
			break;
			//Load master list
		case 2:
			loadMaster();
			break;
			//Store master list
		case 3:
			storeMaster();
			break;
			//Mark absences
		case 4:
			markAbsences();
			break;
			//Edit absences
		case 5:
			editAbsence();
			break;
			//Generate report
		case 6:
			generateReport();
			break;

		case 7:
			exitMenu();
			break;
		}

	} while (selection != 7);
	
}

unsigned int Menu::displayMenu()
{
	unsigned int selection = 0;
	do
	{
		cout << "Main menu\n1. Import course list\n2. Load master list\n3. Store Master List\n";
		cout << "4. Mark absences\n5. Edit absences\n6. Generate Report\n7. Exit program\n";
		cout << "Please enter your selection: ";
		cin >> selection;

		if (selection < 1 || selection > 7)
		{
			cout << "Please enter a valid selection from 1 to 7. Thank you." << endl;
			pause();
		}

	} while (selection < 1 || selection > 7);
	system("CLS");

	return selection;
}

void Menu::pause()
{
	cout << "Press any key to continue";
	cin.ignore();
	cin.get();
	system("CLS");
}

void Menu::importRecords()
{
	std::ifstream classRecords;

	//checks for preexisting list
	if (mpStudentList != nullptr)
	{
		//deletes existing list
		delete mpStudentList;
	}

	//open file
	classRecords.open("classList.csv", std::ios::in);
	if (!classRecords.eof())
	{
		//create empty list
		mpStudentList = new List<Node<Data>>;
		char line[50];
		//remove header line
		classRecords.getline(line, 50);

		while (!classRecords.eof())
		{
			Data newData;
			//store record number
			classRecords.getline(line, 50, ',');
			newData.setRecord(atoi(line));
			//store ID number
			classRecords.getline(line, 50, ',');
			newData.setID(atoi(line));
			//store last name
			std::string s;
			classRecords.getline(line, 50, '"');
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setLastName(s);
			//store first name
			classRecords.getline(line, 50, '"');
			s = line;
			newData.setFirstName(s);
			classRecords.getline(line, 50, ',');
			//store email
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setEmail(s);
			//store credits
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setCredits(s);
			//store major
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setProgram(s);
			//store standing
			classRecords.getline(line, 50);
			s = line;
			newData.setStanding(s);

			//create the new node using these values
			insertNewAtFront(newData);
		}

		cout << "Student list imported correctly." << endl;

	}
	else
	{
		cout << "Could not find student list. Not imported to system." << endl;
	}
}

void Menu::insertNewAtFront(Data& newData)
{
	//get new node to add to front of list
	Node<Data>* newNode = mpStudentList->createNewNode(newData);

	//empty list
	if (mpStudentList->getHeadPtr() == nullptr)
	{
		mpStudentList->setHeadPtr(newNode);
	}
	//non-empty list
	else
	{
		newNode->setNext(mpStudentList->getHeadPtr());
		mpStudentList->setHeadPtr(newNode);
	}
}

std::string Menu::getTime()
{
	//get time from device
	std::time_t time = std::time(0);
	std::tm* now = std::localtime(&time);

	//format time into string for storage
	char dateChar[15];
	strftime(dateChar, 15, "%x", now);

	return std::string() = dateChar;
}

void Menu::markAbsences()
{
	std::string todaysDate = getTime();

	Node<Data>* curr = mpStudentList->getHeadPtr();

	while (curr != nullptr)
	{
		int absent;
		do
		{
			absent = 0;
			//Prompt for student attendance
			cout << "Is " << curr->getData()->getFirstName()
				<< " " << curr->getData()->getLastName()
				<< " absent?" << endl;
			cout << "1. Yes or 2. No\nEnter 1 or 2: ";
			cin >> absent;
			//If incorrect integer used
			if (absent != 1 && absent != 2)
			{
				cout << "Please enter either 1 or 2." << endl;
				pause();
			}

		} while (absent != 1 && absent != 2);

		//add absence date if absent today
		if (absent == 1)
		{
			curr->getData()->addAbsence(todaysDate);
		}

		//Move to next student
		curr = curr->getNext();
		system("CLS");
	}
	cout << "Absences entered correctly." << endl;
}

void Menu::generateReport()
{
	int selection = 0;

	do
	{
		cout << "Would you like to:\n"
			<< "1. Generate a report showing all students, the number of times they've been absent, and their most resent absence"
			<< "\nor\n"
			<< "2. Generate a report showing only students who have been absent a certain number of times (entered by user)"
			<< "\nEnter selection: ";
		cin >> selection;

		if (selection != 1 && selection != 2)
		{
			cout << "Please enter either 1 or 2." << endl;
			pause();
		}

	} while (selection != 1 && selection != 2);

	system("CLS");

	//Generate only absent threshold-meeting students 
	if (selection == 2)
	{
		unsigned int numAbsences = 0;
		do
		{
			cout << "Please enter the absence threshold you would like for the report (integer): ";
			cin >> numAbsences;

			if (numAbsences < 1)
			{
				cout << "Please enter an integer larger than 0" << endl;
				pause();
			}

		} while (numAbsences < 1);

		system("CLS");

		printThreshold(numAbsences);
	}
	//Generate report for all students
	else
	{
		printAll();
	}
}

void Menu::printAll()
{
	std::ofstream report("StudentAbsences.txt");

	Node<Data>* curr = mpStudentList->getHeadPtr();

	
	//Print header to file
	report << std::left
		<< std::setw(20) << "Name"
		<< std::setw(10) << "Absences"
		<< "Last Absence" << endl;

	//Print header to screen
	cout << std::left << "Report also generated to StudentAbsences.txt file." << endl;
	cout << std::setw(20) << "Name"
		<< std::setw(10) << "Absences"
		<< "Last Absence" << endl;

	while (curr != nullptr)
	{
		//Print student info to file
		report << std::setw(10) << curr->getData()->getLastName()
			<< std::setw(10) << curr->getData()->getFirstName()
			<< std::setw(10) << curr->getData()->getNumAbsences()
			<< curr->getData()->getLastAbsence() << endl;

		//Print student info to screnn
		cout << std::setw(10) << curr->getData()->getLastName()
			<< std::setw(10) << curr->getData()->getFirstName()
			<< std::setw(10) << curr->getData()->getNumAbsences()
			<< curr->getData()->getLastAbsence() << endl;

		//Move to next student
		curr = curr->getNext();
	}

	report.close();

	pause();
}

void Menu::printThreshold(unsigned int numAbsences)
{
	std::ofstream report("RequestedAbsences.txt");

	Node<Data>* curr = mpStudentList->getHeadPtr();

	//print header to file
	report << std::left << "Students who missed " << numAbsences << " or more classes." << endl;

	//print header to screen
	cout << std::left << "Report also generated to RequestedAbsences.txt file." << endl;
	cout << "Students who missed " << numAbsences << " or more classes." << endl;

	while (curr != nullptr)
	{
		if (curr->getData()->getNumAbsences() >= numAbsences)
		{
			//print to file
			report << std::setw(10) << curr->getData()->getLastName()
				<< ", "
				<< curr->getData()->getFirstName()
				<< endl;

			//print to screen
			cout << std::setw(10) << curr->getData()->getLastName()
				<< ", "
				<< curr->getData()->getFirstName()
				<< endl;
		}
		//move to next student
		curr = curr->getNext();
	}

	report.close();

	pause();
}

void Menu::storeMaster()
{
	std::ofstream master("master.csv");

	Node<Data>* curr = mpStudentList->getHeadPtr();

	int absences, index;

	while (curr != nullptr)
	{
		//set number of absences
		absences = curr->getData()->getNumAbsences();
		index = 0;

		//Print student records
		master << curr->getData()->getRecord() << ","
			<< curr->getData()->getID() << ","
			<< curr->getData()->getLastName() << ","
			<< curr->getData()->getFirstName() << ","
			<< curr->getData()->getEmail() << ","
			<< curr->getData()->getCredits() << ","
			<< curr->getData()->getProgram() << ","
			<< curr->getData()->getStanding() << ","
			<< absences << ",";

		//Print however many absences student has
		while (index < absences)
		{
			master << curr->getData()->getAbsence(index) << ",";
			index++;
		}

		master << endl;

		//move to next student
		curr = curr->getNext();
	}

	master.close();

	cout << "Master list stored successfully." << endl;
}

void Menu::loadMaster()
{
	std::ifstream classRecords;

	//checks for preexisting list
	if (mpStudentList != nullptr)
	{
		//deletes existing list
		delete mpStudentList;
	}

	//open file
	classRecords.open("master.csv", std::ios::in);
	if (classRecords.good())
	{
		//create empty list
		mpStudentList = new List<Node<Data>>;
		char line[50];

		while (classRecords.good())
		{
			Data newData;
			//store record number
			classRecords.getline(line, 50, ',');
			newData.setRecord(atoi(line));
			//store ID number
			classRecords.getline(line, 50, ',');
			newData.setID(atoi(line));
			//store last name
			std::string s;
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setLastName(s);
			//store first name
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setFirstName(s);
			//store email
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setEmail(s);
			//store credits
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setCredits(s);
			//store major
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setProgram(s);
			//store standing
			classRecords.getline(line, 50, ',');
			s = line;
			newData.setStanding(s);
			//store num absences
			classRecords.getline(line, 50, ',');
			newData.setAbsences(atoi(line));
			//store absence dates
			for (int index = 0; index < newData.getNumAbsences(); index++)
			{
				classRecords.getline(line, 50, ',');
				s = line;
				newData.addAbsence(s);
				newData.setAbsences(newData.getNumAbsences() - 1);
			}

			//create the new node using these values
			insertNewAtFront(newData);
		}

		//delete empty node created because '\n'
		Node<Data>* bad = mpStudentList->getHeadPtr();
		mpStudentList->setHeadPtr(mpStudentList->getHeadPtr()->getNext());
		delete bad;

		cout << "Master list loaded correctly." << endl;

	}
	else
	{
		cout << "Could not find master list. Not loaded to system." << endl;
	}
}

void Menu::editAbsence()
{
	unsigned int studentID = 0, success = 0;

	cout << "Please enter the ID of the student whose absences you would like to edit:  ";
	cin >> studentID;

	Node<Data>* curr = mpStudentList->getHeadPtr();

	while (curr != nullptr)
	{
		if (curr->getData()->getID() == studentID)
		{
			//found specified student
			success = 1;
			break;
		}

		curr = curr->getNext();
	}

	system("CLS");

	//found student
	if (success == 1)
	{
			cout << studentID << " (" << curr->getData()->getFirstName() << ") absence date(s):" << endl;
			//Print current absences
			for (int index = 0; index < curr->getData()->getNumAbsences(); index++)
			{
				cout << curr->getData()->getAbsence(index) << endl;
			}

			std::string date;
			//get wanted date removed
			cout << "Please enter which of these dates would you like to remove (enter in the format seen): ";
			cin >> date;
			
			system("CLS");

			bool deleteSuccess = curr->getData()->removeAbsence(date);

			if (deleteSuccess)
			{
				cout << date << " absence removed successfully." << endl;
			}
			else
			{
				cout << "Sorry, unable to remove absence with " << date << " date." << endl;
			}

	}
	//didn't find student
	else
	{
		system("CLS");
		cout << "Sorry, was unable to find a student with the ID number " << studentID << "." << endl;
	}

	pause();
}

void Menu::exitMenu()
{
	int selection = 0;
	do
	{
		cout << "Would you like to store your master list before exiting?"
			<< "\n1. Yes\nor\n2. No\n"
			<< "Please enter selection: ";
		
		cin >> selection;

		if (selection != 1 && selection != 2)
		{
			cout << "Please enter either \"1\" or \"2\". Thank you." << endl;

			pause();
		}
		else
		{
			system("CLS");
		}

	} while (selection != 1 && selection != 2);

	if (selection == 1)
	{
		storeMaster();
	}

	cout << "Thank you for using HatchettSharp software. Have a great day!" << endl;

}