#include "Hospital.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<ctime>

using namespace std;

Patient::Patient(string a, string b, int x, string c, int y)
{
	patientID = a;
	name = b;
	age = x;
	condition = c;
	priorityLevel = y;
}
string Patient::getID() const { return patientID; }
string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
string Patient::getCondition() const { return condition; }
int Patient::getPriorityLevel() const { return priorityLevel; }
void Patient::display() const
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

unsigned long PatientQueue::getHash(const string& password)
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

void PatientQueue::enqueue(const Patient& p)
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

void PatientQueue::peekFront() const
{
	if (head == nullptr) { cout << "\n[ NOTICE: No patient waiting ]" << endl; return; }
	cout << "\n[ NEXT UP FOR TREATMENT ]" << endl;
	head->s.display();
}

void PatientQueue::displayQueue() const
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

PatientQueue::QueueStatistics PatientQueue::calculateQueueStatistics() const
{
	QueueStatistics stats;
	int totalAge = 0;

	Node* temp = head;

	while (temp != nullptr)
	{
		stats.totalPatients++;
		totalAge += temp->s.getAge();

		if (temp->s.getPriorityLevel() == 1)
		{
			stats.criticalCount++;
		}
		else if (temp->s.getPriorityLevel() == 2)
		{
			stats.moderateCount++;
		}
		else if (temp->s.getPriorityLevel() == 3)
		{
			stats.stableCount++;
		}

		temp = temp->next;
	}

	if (stats.totalPatients > 0)
	{
		stats.averageAge =
			static_cast<double>(totalAge) / stats.totalPatients;

		stats.criticalPercentage =
			static_cast<double>(stats.criticalCount) / stats.totalPatients * 100.0;

		stats.moderatePercentage =
			static_cast<double>(stats.moderateCount) / stats.totalPatients * 100.0;

		stats.stablePercentage =
			static_cast<double>(stats.stableCount) / stats.totalPatients * 100.0;
	}

	return stats;
}

void PatientQueue::displayQueueStatistics() const
{
	QueueStatistics stats = calculateQueueStatistics();

	cout << "===== QUEUE STATISTICS ===== " << endl;
	cout << "Total Patients: " << stats.totalPatients << endl;
	cout << "Critical (Priority 1): " << stats.criticalCount << endl;
	cout << "Moderate (Priority 2): " << stats.moderateCount << endl;
	cout << "Stable (Priority 3): " << stats.stableCount << endl;
	cout << "Average Patient Age: "
		<< fixed << setprecision(1) << stats.averageAge << endl;
	cout << "Critical Percentage: "
		<< fixed << setprecision(1) << stats.criticalPercentage << "%" << endl;

	cout << "Moderate Percentage: "
		<< fixed << setprecision(1) << stats.moderatePercentage << "%" << endl;

	cout << "Stable Percentage: "
		<< fixed << setprecision(1) << stats.stablePercentage << "%" << endl;
}

void PatientQueue::saveQueueReport(const string& filename) const
{
	QueueStatistics stats = calculateQueueStatistics();

	string generatedTime = getCurrentTimestamp();

	if (generatedTime.empty())
	{
		return;
	}

	ofstream reportFile(filename);

	if (!reportFile)
	{
		cout << "[!] Error: Unable to open queue report file." << endl;
		return;
	}

	reportFile << "===== QUEUE STATISTICS REPORT =====" << endl;
	reportFile << "Generated: " << generatedTime << endl;
	reportFile << "Total Patients: " << stats.totalPatients << endl;
	reportFile << "Critical (Priority 1): " << stats.criticalCount << endl;
	reportFile << "Moderate (Priority 2): " << stats.moderateCount << endl;
	reportFile << "Stable (Priority 3): " << stats.stableCount << endl;

	reportFile << "Average Patient Age: "
		<< fixed << setprecision(1)
		<< stats.averageAge << endl;

	reportFile << "Critical Percentage: "
		<< fixed << setprecision(1)
		<< stats.criticalPercentage << "%" << endl;

	reportFile << "Moderate Percentage: "
		<< fixed << setprecision(1)
		<< stats.moderatePercentage << "%" << endl;

	reportFile << "Stable Percentage: "
		<< fixed << setprecision(1)
		<< stats.stablePercentage << "%" << endl;

	if (!reportFile)
	{
		cout << "[!] Error: Failed while writing queue report." << endl;
		return;
	}

	reportFile.close();

	if (!reportFile)
	{
		cout << "[!] Error: Failed to finalize queue report file." << endl;
		return;
	}

	cout << "[!] Queue report saved successfully." << endl;
}

void PatientQueue::searchByID(const string& id)
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
	string tempFilename = filename + ".tmp";
	string backupFilename = filename + ".bak";

	ofstream outFile(tempFilename);

	if (!outFile)
	{
		cout << "[!] Error: Unable to open file for saving." << endl;
		return;
	}

	Node* temp = head;
	while (temp != nullptr)
	{
		outFile << temp->s.getID() << "|"
			<< temp->s.getName() << "|"
			<< temp->s.getAge() << "|"
			<< temp->s.getCondition() << "|"
			<< temp->s.getPriorityLevel() << endl;

		temp = temp->next;
	}

	outFile.flush();

	if (!outFile)
	{
		cout << "[!] Error: Failed while writing patient data." << endl;
		outFile.close();
		return;
	}

	outFile.close();

	if (!outFile)
	{
		cout << "[!] Error: Failed to finalize patient data file." << endl;
		return;
	}

	bool originalFileExists = false;

	ifstream originalFile(filename);

	if (originalFile)
	{
		originalFileExists = true;
	}

	originalFile.close();

	if (originalFileExists)
	{
		std::remove(backupFilename.c_str());

		if (std::rename(filename.c_str(), backupFilename.c_str()) != 0)
		{
			cout << "[!] Error: Unable to create backup of existing patient data."
				<< endl;

			std::remove(tempFilename.c_str());
			return;
		}
	}

	if (std::rename(tempFilename.c_str(), filename.c_str()) != 0)
	{
		cout << "[!] Error: Unable to replace patient data file." << endl;

		if (originalFileExists)
		{
			if (std::rename(backupFilename.c_str(), filename.c_str()) != 0)
			{
				cout << "[!] Critical Error: Failed to restore backup patient data."
					<< endl;
			}
			else
			{
				cout << "[!] Previous patient data restored successfully."
					<< endl;
			}
		}

		return;
	}

	cout << "[!] The patient queue saved to file successfully." << endl;
}

void PatientQueue::loadFromFile(string filename)
{
	string backupFilename = filename + ".bak";

	ifstream primaryCheck(filename);
	bool primaryFileExists = static_cast<bool>(primaryCheck);
	primaryCheck.close();

	if (!primaryFileExists)
	{
		ifstream backupCheck(backupFilename);
		bool backupFileExists = static_cast<bool>(backupCheck);
		backupCheck.close();

		if (backupFileExists)
		{
			if (std::rename(backupFilename.c_str(), filename.c_str()) == 0)
			{
				cout << "[!] Recovery: Patient data restored from backup."
					<< endl;
			}
			else
			{
				cout << "[!] Error: Backup patient data exists but could not be restored."
					<< endl;
			}
		}
	}

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
					if (database[i].role == "nurse") { nurseMenu(q, inputUser); }
					if (database[i].role == "doctor") { doctorMenu(q, inputUser); }
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

void PatientQueue::nurseMenu(PatientQueue& q, const string& actor)
{
	int choice;
	string name, patientID, condition, ageInput, priorityInput;
	int age, priorityLevel;
	while (true)
	{
		cout << "\n" << string(20, '-') << " NURSE WORKSTATION " << string(20, '-') << endl;
		cout << "1. Display All Waiting Patients\n2. Register New Patient Entry\n3. Search Patient by ID\n4. View Queue Statistics\n5. Save Queue Report\n6. Logout" << endl;
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

				if (!isValidTextField(name))
				{
					cout << "[!] Invalid patient name. Name cannot be empty or contain'|'."
						<< endl;
					continue;
				}

				break;
			}

			while (true)
			{
				cout << "Please enter the patientID: ";
				getline(cin, patientID);

				if (!isValidTextField(patientID))
				{
					cout << "[!] Invalid patient ID. ID cannot be empty or contain '|'. Please enter a valid ID."
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

				if (!isValidTextField(condition))
				{
					cout << "[!] Invalid patient condition. Condition cannot be empty or contain '|'."
						<< endl;
					continue;
				}

				break;
			}

			while (true)
			{
				cout << "Please enter age: ";
				getline(cin, ageInput);

				if (!parseIntegerInRange(ageInput, 0, 150, age))
				{
					cout << "[!] Invalid age. Please enter a whole number (0-150)."
						<< endl;
					continue;
				}

				break;
			}

			while (true)
			{
				cout << "Please enter priority level (1-3): ";
				getline(cin, priorityInput);

				if (!parseIntegerInRange(priorityInput, 1, 3, priorityLevel))
				{
					cout << "[!] Invalid priority level. Please enter a whole number (1-3)."
						<< endl;
					continue;
				}
				
				break;
			}

			q.enqueue(Patient(patientID, name, age, condition, priorityLevel));
			cout << "The patient is added successfully" << endl;

			writeAuditLog(actor, "NURSE", "REGISTER", patientID);
		}
		else if (choice == 3)
		{
			cout << "Please enter the patient ID: ";
			cin >> patientID;
			q.searchByID(patientID);
		}
		else if (choice == 4)
		{
			q.displayQueueStatistics();
		}
		else if (choice == 5)
		{
			q.saveQueueReport();
		}
		else if (choice == 6)
		{
			cout << "Logging out..." << endl;
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error, please enter a valid number (1-6)!" << endl;
		}
	}
}

void PatientQueue::doctorMenu(PatientQueue& q, const string& actor)
{
	int choice;
	while (true)
	{
		cout << "\n" << string(20, '+') << " DOCTOR INTERFACE " << string(20, '+') << endl;
		cout << "1. Treat Next Patient\n2. Preview Next in Line\n3. View Full Queue\n4. View Queue Statistics\n5. Save Queue Report\n6. Logout" << endl;
		cout << "Selection: ";
		cin >> choice;
		if (choice == 1)
		{
			Patient treatedPatient = q.dequeue();

			if (treatedPatient.getID() != "0")
			{
				writeAuditLog(actor, "DOCTOR", "TREAT", treatedPatient.getID());
				writeTreatmentHistory(treatedPatient, actor);
			}
		}
		else if (choice == 2) { q.peekFront(); }
		else if (choice == 3) { q.displayQueue(); }
		else if (choice == 4) { q.displayQueueStatistics(); }
		else if (choice == 5) { q.saveQueueReport(); }
		else if (choice == 6) { break; }
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error, please enter a valid number (1-6)!" << endl;
		}
	}
}

bool PatientQueue::patientIDExists(const string& id)
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

bool PatientQueue::isValidTextField(const string& value)
{
	if (value.empty())
	{
		return false;
	}

	if (value.find('|') != string::npos)
	{
		return false;
	}

	return true;
}

bool PatientQueue::parseIntegerInRange(const string& input, int minValue, int maxValue, int& result)
{
	try
	{
		size_t pos;
		int parsedValue = stoi(input, &pos);
		if (pos != input.length())
		{
			return false;
		}

		if (parsedValue<minValue || parsedValue>maxValue)
		{
			return false;
		}

		result = parsedValue;
		return true;
	}
	catch (const exception&)
	{
		return false;
	}
}

string PatientQueue::getCurrentTimestamp() const
{
	time_t currentTime = time(nullptr);
	tm localTime{};
	if (localtime_s(&localTime, &currentTime) != 0)
	{
		cout << "[!] Error: Unable to obtain local time." << endl;
		return " ";
	}

	stringstream timestamp;

	timestamp << put_time(&localTime, "%Y-%m-%d %H:%M:%S");

	return timestamp.str();
}

void PatientQueue::writeAuditLog(const string& actor, const string& role, const string& action, const string& patientID) const
{
	string formattedTime = getCurrentTimestamp();

	if (formattedTime.empty())
	{
		return;
	}

	ofstream logFile("audit.log", ios::app);

	if (!logFile)
	{
		cout << "[!] Error: Unable to open audit log file." << endl;
		return;
	}

	logFile << "[" << formattedTime << "] "
		<< actor << " | "
		<< role << " | "
		<< action << " | "
		<< patientID << endl;

	if (!logFile)
	{
		cout << "[!] Error: Failed to finalize audit log file." << endl;
		return;
	}

	logFile.close();

	if (!logFile)
	{
		cout << "[!] Error: Failed while writing audit log." << endl;
		return;
	}
}

void PatientQueue::writeTreatmentHistory(const Patient& patient, const string& doctor) const
{
	string formattedTime = getCurrentTimestamp();

	if (formattedTime.empty())
	{
		return;
	}

	ofstream historyFile("treatment_history.log", ios::app);

	if (!historyFile)
	{
		cout << "Error: Unable to open treatment history file." << endl;
		return;
	}

	historyFile << formattedTime << "|"
		<< doctor << "|"
		<< patient.getID() << "|"
		<< patient.getName() << "|"
		<< patient.getAge() << "|"
		<< patient.getCondition() << "|"
		<< patient.getPriorityLevel() << endl;

	if (!historyFile)
	{
		cout << "[!] Error: Failed while writing treatment history." << endl;
		return;
	}

	historyFile.close();

	if (!historyFile)
	{
		cout << "[!] Error: Failed to finalize treatment history file." << endl;
		return;
	}
}

void PatientQueue::clear()
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

PatientQueue::~PatientQueue()
{
	clear();
}