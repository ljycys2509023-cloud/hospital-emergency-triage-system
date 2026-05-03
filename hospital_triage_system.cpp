#include<iostream> 
#include<string> 
#include<iomanip>
using namespace std;
class Patient
{
private:
	string patientID;
	string name;
	int age;
	string condition;
int priorityLevel;
public:
	Patient(string a, string b, int x, string c, int y)
	{
		patientID = a;
		name = b;
		age = x;
		condition = c;
		priorityLevel = y;
	}
	string getID() { return patientID; }
	string getName() { return name; }
	int getAge() { return age; }
	string getCondition() { return condition; }
	int getPriorityLevel() { return priorityLevel; }
	void display()
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
};

class PatientQueue {
private:
	struct Node
	{
		Patient s;
		Node* next;
		Node(Patient patient_obj) : s(patient_obj), next(nullptr) {}
	};
Node* head = nullptr;

	unsigned long getHash(string password)
	{
		unsigned long hashValue = 5381;
		for (char c : password)
		{
			hashValue = hashValue * 33 + c;
		}
		return hashValue;
	}

	struct account
	{
		string username;
		unsigned long passwordHash;
		string role;
	};
//set up a small database
account database[2];

	void setupAccounts()
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


public:
	void enqueue(Patient p)
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
	Patient dequeue()
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
	void peekFront()
	{
		if (head == nullptr) { cout << "\n[ NOTICE: No patient waiting ]" << endl; return; }
		cout << "\n[ NEXT UP FOR TREATMENT ]" << endl;
		head->s.display();
	}
	void displayQueue()
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
	void searchByID(string id)
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

	

	void log(PatientQueue& q)
	{
		setupAccounts();

		string inputUser;
		string inputPass;

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
					unsigned long inputHash = getHash(inputPass);

					//compare the two hashvalue
					if (inputHash == database[i].passwordHash)
					{
						cout << "\n[!] Login Successful! Welcome " << inputUser << "!" << endl;
						loginSuccess = true;

						//open the role menu
						if (database[i].role == "nurse") { nurseMenu(q); }
						if (database[i].role == "doctor") { doctorMenu(q); }
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

	void nurseMenu(PatientQueue& q)
	{
		int choice;
		string name, patientID, condition;
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
				cout << "Please enter the patient's name: ";
				getline(cin, name);
				cout << "Please enter the patientID: ";
				getline(cin, patientID);
				cout << "Please enter the ill condition: ";
				getline(cin, condition);
				while (true) 
				{
					cout << "Please enter age: ";
					if (cin >> age && age >= 0 && age <= 150) 
					{
						break;
					}
					else 
					{
						cout << "[!] Invalid age. Please enter a number (0-150)." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
					}
				}
				cout << "Please enter priority level (1-3): ";
				cin >> priorityLevel;
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
	void doctorMenu(PatientQueue& q)
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
	~PatientQueue()
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
};
int main() {
	PatientQueue p;
	p.enqueue(Patient("P001", "Ahmad", 25, "Heart Attack", 1));
	p.enqueue(Patient("P002", "Siti", 40, "Common Cold", 3));
	p.enqueue(Patient("P003", "John", 60, "Severe Asthma", 2));
	p.enqueue(Patient("P004", "Wong", 12, "Head Injury", 1));
	p.enqueue(Patient("P005", "Zali", 33, "Abdominal Pain", 2));
	p.enqueue(Patient("P006", "Tan", 55, "Skin Rash", 3));
	p.log(p);
	return 0;
}