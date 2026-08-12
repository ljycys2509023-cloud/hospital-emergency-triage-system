#include "Hospital.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>

using namespace std;

Patient::Patient(string a, string b, int x, string c, int y)
{
	patientID = a;
	name = b;
	age = x;
	condition = c;
	priorityLevel = y;
}
string Patient::getID() { return patientID; }
string Patient::getName() { return name; }
int Patient::getAge() { return age; }
string Patient::getCondition() { return condition; }
int Patient::getPriorityLevel() { return priorityLevel; }
void Patient::display()
{
	cout << left << setw(20) << "Patient ID" << ": " << patientID << endl;
	cout << left << setw(20) << "Name" << ": " << name << endl;
	cout << left << setw(20) << "Age" << ": " << age << endl;
	cout << left << setw(20) << "Clinical Note" << ": " << condition << endl;
	cout << left << setw(20) << "Priority Status" << ": ";
	switch (priorityLevel)
	{
	case 1: cout << "CRITICAL (Immediate Attention)"; break;
	case 2: cout << "MODERATE (Urgent)"; break;
	case 3: cout << "MILD (Standard)"; break;
	}
	cout << endl;
}


PatientQueue::PatientQueue()
{
	head = nullptr;
	setupAccounts();
}

unsigned long PatientQueue::getHash(string password)
{
	unsigned long hashValue = 5381;
	for (char c : password)
	{
		hashValue = hashValue * 33 + c;
	}
	return hashValue;
}

void PatientQueue::setupAccounts()
{
	// set up the nurse account
	database[0].username = "nurse1";
	database[0].passwordHash = getHash("123"); // password is 123, and system will store the hash value
	database[0].role = "nurse";

	// set up the doctor account
	database[1].username = "doc1";
	database[1].passwordHash = getHash("888"); // password is 888, and system will store the hash value
	database[1].role = "doctor";
}

void PatientQueue::enqueue(Patient p)
{
	Node* X = new Node(p);
	if (head == nullptr || p.getPriorityLevel() < head->s.getPriorityLevel())
	{
		X->next = head;
		head = X;
		return;
	}
	Node* temp = head;
	while (temp->next != nullptr && temp->next->s.getPriorityLevel() <= X->s.getPriorityLevel())
	{
		temp = temp->next;
	}
	X->next = temp->next;
	temp->next = X;
}

Patient PatientQueue::dequeue()
{
	if (head == nullptr) {
		cout << "\n[ NOTICE: The queue is currently empty ]" << endl;
		return Patient("0", "None", 0, "None", 3);
	}
	Node* t = head;
	Patient p = t->s;
	head = head->next;
	delete t;
	cout << "\n" << string(20, '*') << " CALLING PATIENT " << string(20, '*') << endl;
	p.display();
	return p;
}

void PatientQueue::peekFront()
{
	if (head == nullptr) { cout << "\n[ NOTICE: No patient waiting ]" << endl; return; }
	cout << "\n[ NEXT UP FOR TREATMENT ]" << endl;
	head->s.display();
}

void PatientQueue::displayQueue()
{
	if (head == nullptr) { cout << "\n[ NOTICE: Queue is empty ]" << endl; return; }
	Node* temp = head;
	int count = 1;
	cout << "\n" << string(30, '=') << " LIVE HOSPITAL QUEUE " << string(30, '=') << endl;
	cout << left << setw(6) << "Pos" << setw(18) << "Patient Name" << setw(12) << "ID" << setw(25) << "Condition" << "Status" << endl;
	cout << string(80, '-') << endl;
	while (temp != nullptr)
	{
		cout << left << "No." << setw(3) << count << setw(18) << temp->s.getName() << setw(12) << temp->s.getID() << setw(25) << temp->s.getCondition();
		switch (temp->s.getPriorityLevel())
		{
		case 1: cout << "[CRITICAL]"; break;
		case 2: cout << "[MODERATE]"; break;
		case 3: cout << "[MILD]"; break;
		}
		cout << endl;
		count++;
		temp = temp->next;
	}
	cout << string(80, '=') << endl;
}

void PatientQueue::searchByID(string id)
{
	Node* temp = head;
	while (temp != nullptr)
	{
		if (temp->s.getID() == id)
		{
			cout << "\n[ RECORD RETRIEVED FOR ID: " << id << " ]" << endl;
			temp->s.display();
			return;
		}
		temp = temp->next;
	}
	cout << "\n[ ERROR: Record " << id << " not found in current queue ]" << endl;
}

void PatientQueue::saveToFile(string filename)
{
	ofstream outFile(filename);

	if (!outFile)
	{
		cout << "[!] Error: Unable to open file for saving." << endl;
		return;
	}

	Node* temp = head;
	while (temp != NULL)
	{
		outFile << temp->s.getID() << "|"
			<< temp->s.getName() << "|"
			<< temp->s.getAge() << "|"
			<< temp->s.getCondition() << "|"
			<< temp->s.getPriorityLevel() << endl;

		temp = temp->next;
	}

	outFile.close();
	cout << "[!]The patient queue saved to file successfully" << endl;
}

void PatientQueue::loadFromFile(string filename)
{
	ifstream infile(filename);

	if (!infile)
	{
		cout << "[!] No previous patient record found. Starting with default queue." << endl;
		return;
	}

	string patientID;
	string name;
	string ageText;
	string condition;
	string priorityText;
	string line;

	int recordCount = 0;
	int skippedCount = 0;

	while (getline(infile, line))
	{
		stringstream ss(line);

		if (!getline(ss, patientID, '|') ||
			!getline(ss, name, '|') ||
			!getline(ss, ageText, '|') ||
			!getline(ss, condition, '|') ||
			!getline(ss, priorityText))
		{
			cout << "[!] Warning: Incomplete patient record detected. Record skipped."
				<< endl;

			skippedCount++;
			continue;
		}

		if (patientID.empty() || name.empty() || condition.empty())
		{
			cout << "[!] Warning: Missing required data in patient record. "
				<< "Record skipped." << endl;
			skippedCount++;
			continue;
		}
		if (patientIDExists(patientID))
		{
			cout << "[!] Warning: Duplicate patient ID "
				<< patientID << ". Record skipped." << endl;

			skippedCount++;
			continue;
		}

		try
		{
			size_t agePos;
			int age = stoi(ageText, &agePos);
			if (agePos != ageText.length())
			{
				cout << "[!] Warning: Invalid age format for patient "
					<< patientID << ". Record skipped." << endl;

				skippedCount++;
				continue;
			}
			if (age < 0 || age > 150)
			{
				cout << "[!] Warning: Invalid age for patient "
					<< patientID << ". Record skipped." << endl;
				skippedCount++;
				continue;
			}
			
			size_t priorityPos;
			int priorityLevel = stoi(priorityText, &priorityPos);
			if (priorityPos != priorityText.length())
			{
				cout << "[!] Warning: Invalid priority format for patient "
					<< patientID << ". Record skipped." << endl;

				skippedCount++;
				continue;
			}
			if (priorityLevel < 1 || priorityLevel > 3)
			{
				cout << "[!] Warning: Invalid priority level for patient "
					<< patientID << ". Record skipped." << endl;
				skippedCount++;
				continue;
			}

			enqueue(Patient(patientID, name, age, condition, priorityLevel));
			recordCount++;
		}
		catch (const exception&)
		{
			cout << "[!] Warning: Invalid numerical data for patient "
				<< patientID << ". Record skipped." << endl;
			skippedCount++;
		}
	}

	cout << "[!] Patient records loaded successfully: "
		<< recordCount << endl;
	if (skippedCount > 0)
	{
		cout << "[!] Invalid records skipped: "
			<< skippedCount << endl;
	}
}

void PatientQueue::log(PatientQueue& q)
{
	string inputUser;
	string inputPass;

	const int MAX_ATTEMPTS = 5;
	const auto LOCKOUT_DURATION = std::chrono::seconds(30);

	while (true)
	{
		cout << "\n" << string(20, '#') << " SYSTEM LOGIN " << string(20, '#') << endl;
		cout << "Enter username or 'exit' to shut down: ";
		cin >> inputUser;
		if (inputUser == "exit") { cout << "System shutting down..." << endl; break; }

		cout << "Enter password: ";
		cin >> inputPass;

		//begin checking
		bool loginSuccess = false;

		//search the user name in database
		for (int i = 0; i < 2; i++)
		{
			if (database[i].username == inputUser)//find the name, then calculate the password's hashvalue
			{
				if (database[i].failedAttempts >= MAX_ATTEMPTS)
				{
					if (std::chrono::steady_clock::now() < database[i].lockoutUntil)
					{
						break;
					}
					else
					{
						database[i].failedAttempts = 0;
					}
				}

				unsigned long inputHash = getHash(inputPass);

				//compare the two hashvalue
				if (inputHash == database[i].passwordHash)
				{
					database[i].failedAttempts = 0;

					cout << "\n[!] Login Successful! Welcome " << inputUser << "!" << endl;
					loginSuccess = true;

					//open the role menu
					if (database[i].role == "nurse") { nurseMenu(q); }
					if (database[i].role == "doctor") { doctorMenu(q); }
				}
				else
				{
					database[i].failedAttempts++;
					if (database[i].failedAttempts == MAX_ATTEMPTS)
					{
						database[i].lockoutUntil =
							std::chrono::steady_clock::now() + LOCKOUT_DURATION;
					}
				}

				break;
			}
		}

		if (loginSuccess == false)
		{
			cout << "\n[i] Login Failed: Incorrect username or password." << endl;
		}
	}
}

void PatientQueue::nurseMenu(PatientQueue& q)
{
	int choice;
	string name, patientID, condition, ageInput, priorityInput;
	int age, priorityLevel;
	while (true)
	{
		cout << "\n" << string(20, '-') << " NURSE WORKSTATION " << string(20, '-') << endl;
		cout << "1. Display All Waiting Patients\n2. Register New Patient Entry\n3. Search Patient by ID\n4. Logout" << endl;
		cout << "Selection: ";
		cin >> choice;
		if (choice == 1)
		{
			displayQueue();
		}
		else if (choice == 2)
		{
			cin.ignore(1000, '\n');

			while (true)
			{
				cout << "Please enter the patient's name: ";
				getline(cin, name);

				if (name.empty())
				{
					cout << "[!] Patient name cannot be empty. Please enter a valid name."
						<< endl;

					continue;
				}

				if (name.find('|') != string::npos)
				{
					cout << "[!] Patient name cannot contain '|'. Please enter a valid name."
						<< endl;

					continue;
				}

				break;
			}

			while (true)
			{
				cout << "Please enter the patientID: ";
				getline(cin, patientID);

				if (patientID.empty())
				{
					cout << "[!] Patient ID cannot be empty. Please enter a valid ID."
						<< endl;

					continue;
				}
				if (patientID.find('|') != string::npos)
				{
					cout << "[!] Patient ID cannot contain '|'. Please enter a valid ID."
						<< endl;

					continue;
				}
				if (patientIDExists(patientID))
				{
					cout << "[!] Patient ID already exists. Please enter a unique ID."
						<< endl;
				}
				else
				{
					break;
				}
			}

			while (true)
			{
				cout << "Please enter the ill condition: ";
				getline(cin, condition);

				if (condition.empty())
				{
					cout << "[!] Patient ill condition cannot be empty. Please enter a valid ill condition."
						<< endl;

					continue;
				}

				if (condition.find('|') != string::npos)
				{
					cout << "[!] Patient ill condition cannot contain '|'. Please enter a valid ill condition."
						<< endl;

					continue;
				}

				break;
			}

			while (true)
			{
				cout << "Please enter age: ";
				getline(cin, ageInput);

				try
				{
					size_t agePos;
					age = stoi(ageInput, &agePos);

					if (agePos != ageInput.length())
					{
						cout << "[!] Invalid age format. Please enter a whole number (0-150)."
							<< endl;

						continue;
					}

					if (age < 0 || age > 150)
					{
						cout << "[!] Invalid age. Please enter a number (0-150)."
							<< endl;

						continue;
					}

					break;
				}
				catch (const exception&)
				{
					cout << "[!] Invalid age format. Please enter a whole number (0-150)."
						<< endl;
				}
			}

			while (true)
			{
				cout << "Please enter priority level (1-3): ";
				getline(cin, priorityInput);

				try
				{
					size_t priorityPos;
					priorityLevel = stoi(priorityInput, &priorityPos);

					if (priorityPos != priorityInput.length())
					{
						cout << "[!] Invalid priority level format. Please enter a whole number (1-3)."
							<< endl;

						continue;
					}

					if (priorityLevel < 1 || priorityLevel > 3)
					{
						cout << "[!] Invalid priority level. Please enter a number (1-3)."
							<< endl;

						continue;
					}

					break;
				}
				catch (const exception&)
				{
					cout << "[!] Invalid priority level format. Please enter a whole number (1-3)."
						<< endl;
				}
			}

			q.enqueue(Patient(patientID, name, age, condition, priorityLevel));
			cout << "The patient is added successfully" << endl;
		}
		else if (choice == 3)
		{
			cout << "Please enter the patient ID: ";
			cin >> patientID;
			q.searchByID(patientID);
		}
		else if (choice == 4)
		{
			cout << "Logging out..." << endl;
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error, please enter a valid number (1-4)!" << endl;
		}
	}
}

void PatientQueue::doctorMenu(PatientQueue& q)
{
	int choice;
	while (true)
	{
		cout << "\n" << string(20, '+') << " DOCTOR INTERFACE " << string(20, '+') << endl;
		cout << "1. Treat Next Patient\n2. Preview Next in Line\n3. View Full Queue\n4. Logout" << endl;
		cout << "Selection: ";
		cin >> choice;
		if (choice == 1) { q.dequeue(); }
		else if (choice == 2) { q.peekFront(); }
		else if (choice == 3) { q.displayQueue(); }
		else if (choice == 4) { break; }
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error, please enter a valid number (1-4)!" << endl;
		}
	}
}

bool PatientQueue::patientIDExists(string id)
{
	Node* temp = head;
	while (temp != nullptr)
	{
		if (temp->s.getID() == id)
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}

PatientQueue::~PatientQueue()
{
	Node* temp = head;
	while (temp != nullptr)
	{
		Node* nextNode = temp->next;
		delete temp;
		temp = nextNode;
	}
	head = nullptr;
}