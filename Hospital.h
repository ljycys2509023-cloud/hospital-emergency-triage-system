#ifndef HOSPITAL_H
#define HOSPITAL_H

#include<string>

class Patient
{
private:
	std::string patientID;
	std::string name;
	int age;
	std::string condition;
	int priorityLevel;
public:
	Patient(std::string a, std::string b, int x, std::string c, int y);
	std::string getID();
	std::string getName();
	int getAge();
	std::string getCondition();
	int getPriorityLevel();
	void display();
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

	unsigned long getHash(std::string password);

	struct account
	{
		std::string username;
		unsigned long passwordHash = 0;
		std::string role;
	};
	//set up a small database
	account database[2];

	void setupAccounts();


public:
	PatientQueue();

	void enqueue(Patient p);

	Patient dequeue();

	void peekFront();

	void displayQueue();

	void searchByID(std::string id);

	void log(PatientQueue& q);

	void nurseMenu(PatientQueue& q);

	void doctorMenu(PatientQueue& q);

	void saveToFile(std::string filename);

	void loadFromFile(std::string filename);

	~PatientQueue();
};

#endif // !HOSPITAL_H

