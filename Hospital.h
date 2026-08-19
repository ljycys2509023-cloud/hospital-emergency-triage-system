#ifndef HOSPITAL_H
#define HOSPITAL_H

#include<chrono>
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
	std::string getID() const;
	std::string getName() const;
	int getAge() const;
	std::string getCondition() const;
	int getPriorityLevel() const;
	void display() const;
};

class PatientQueue {
private:
	struct Node
	{
		Patient s;
		Node* next;
		Node(const Patient& patient_obj) : s(patient_obj), next(nullptr) {}
	};
	Node* head = nullptr;
	bool patientIDExists(const std::string& id);
	bool isValidTextField(const std::string& value);
	bool parseIntegerInRange(const std::string& input, int minValue, int maxValue, int& result);

	void clear();

	std::string getCurrentTimestamp() const;

	void writeAuditLog(const std::string& actor, const std::string& role, const std::string& action, const std::string& patientID) const;

	void writeTreatmentHistory(const Patient& patient, const std::string& doctor) const;

	unsigned long getHash(const std::string& password);

	struct account
	{
		std::string username;
		unsigned long passwordHash = 0;
		std::string role;
		int failedAttempts = 0;
		std::chrono::steady_clock::time_point lockoutUntil;
	};
	//set up a small database
	account database[2];

	void setupAccounts();

	struct QueueStatistics
	{
		int totalPatients = 0;
		int criticalCount = 0;
		int moderateCount = 0;
		int stableCount = 0;

		double averageAge = 0.0;
		double criticalPercentage = 0.0;
		double moderatePercentage = 0.0;
		double stablePercentage = 0.0;
	};

	QueueStatistics calculateQueueStatistics() const;

public:
	PatientQueue();

	PatientQueue(const PatientQueue&) = delete;
	PatientQueue& operator=(const PatientQueue&) = delete;

	void enqueue(const Patient& p);

	Patient dequeue();

	void peekFront() const;

	void displayQueue() const;

	void displayQueueStatistics() const;

	void saveQueueReport() const;

	void searchByID(const std::string& id);

	void log(PatientQueue& q);

	void nurseMenu(PatientQueue& q, const std::string& actor);

	void doctorMenu(PatientQueue& q, const std::string& actor);

	void saveToFile(std::string filename);

	void loadFromFile(std::string filename);

	~PatientQueue();
};

#endif