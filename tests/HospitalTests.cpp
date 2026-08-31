#include <iostream>
#include <string>
#include<cstdio>
#include<fstream>
#include <type_traits>
#include "Hospital.h"

using namespace std;

static_assert(
    !std::is_copy_constructible<PatientQueue>::value,
    "PatientQueue must not be copy constructible");

static_assert(
    !std::is_copy_assignable<PatientQueue>::value,
    "PatientQueue must not be copy assignable");

int passedTests = 0;
int failedTests = 0;

void check(bool condition, const string& testName)
{
    if (condition)
    {
        cout << "[PASS] " << testName << endl;
        passedTests++;
    }
    else
    {
        cout << "[FAIL] " << testName << endl;
        failedTests++;
    }
}

void testPatientModel()
{
    Patient patient("T001", "Alice", 30, "Chest Pain", 2);

    check(patient.getID() == "T001", "Patient ID getter");
    check(patient.getName() == "Alice", "Patient name getter");
    check(patient.getAge() == 30, "Patient age getter");
    check(patient.getCondition() == "Chest Pain", "Patient condition getter");
    check(patient.getPriorityLevel() == 2, "Patient priority getter");
}

void testPriorityOrdering()
{
    PatientQueue queue;

    queue.enqueue(Patient("T003", "Stable Patient", 30, "Test", 3));
    queue.enqueue(Patient("T001", "Critical Patient", 30, "Test", 1));
    queue.enqueue(Patient("T002", "Moderate Patient", 30, "Test", 2));

    Patient first = queue.dequeue();
    Patient second = queue.dequeue();
    Patient third = queue.dequeue();

    check(first.getID() == "T001",
        "Priority queue serves critical patient first");

    check(second.getID() == "T002",
        "Priority queue serves moderate patient second");

    check(third.getID() == "T003",
        "Priority queue serves stable patient last");
}

void testEqualPriorityFIFO()
{
    PatientQueue queue;

    queue.enqueue(Patient("F001", "First Patient", 30, "Test", 2));
    queue.enqueue(Patient("F002", "Second Patient", 30, "Test", 2));
    queue.enqueue(Patient("F003", "Third Patient", 30, "Test", 2));

    Patient first = queue.dequeue();
    Patient second = queue.dequeue();
    Patient third = queue.dequeue();

    check(first.getID() == "F001",
        "Equal-priority patients preserve FIFO order: first");

    check(second.getID() == "F002",
        "Equal-priority patients preserve FIFO order: second");

    check(third.getID() == "F003",
        "Equal-priority patients preserve FIFO order: third");
}

void testEmptyQueueDequeue()
{
    PatientQueue queue;

    Patient result = queue.dequeue();

    check(result.getID() == "0",
        "Dequeue from empty queue returns sentinel patient");

    check(result.getName() == "None",
        "Empty queue sentinel has expected name");

    check(result.getAge() == 0,
        "Empty queue sentinel has expected age");
}

void testMixedPriorityAndFIFO()
{
    PatientQueue queue;

    queue.enqueue(Patient("M001", "Stable First", 30, "Test", 3));
    queue.enqueue(Patient("M002", "Critical First", 30, "Test", 1));
    queue.enqueue(Patient("M003", "Moderate First", 30, "Test", 2));
    queue.enqueue(Patient("M004", "Critical Second", 30, "Test", 1));
    queue.enqueue(Patient("M005", "Moderate Second", 30, "Test", 2));
    queue.enqueue(Patient("M006", "Stable Second", 30, "Test", 3));

    Patient first = queue.dequeue();
    Patient second = queue.dequeue();
    Patient third = queue.dequeue();
    Patient fourth = queue.dequeue();
    Patient fifth = queue.dequeue();
    Patient sixth = queue.dequeue();

    check(first.getID() == "M002",
        "Mixed queue: first critical patient served first");

    check(second.getID() == "M004",
        "Mixed queue: second critical patient preserves FIFO");

    check(third.getID() == "M003",
        "Mixed queue: first moderate patient served next");

    check(fourth.getID() == "M005",
        "Mixed queue: second moderate patient preserves FIFO");

    check(fifth.getID() == "M001",
        "Mixed queue: first stable patient served after higher priorities");

    check(sixth.getID() == "M006",
        "Mixed queue: second stable patient preserves FIFO");
}

void testPersistenceRoundTrip()
{
    const string testFile = "test_patient_data.txt";
    const string tempFile = testFile + ".tmp";
    const string backupFile = testFile + ".bak";

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());

    PatientQueue originalQueue;

    originalQueue.enqueue(
        Patient("PTEST1", "Persistence One", 28, "Test Condition A", 1));

    originalQueue.enqueue(
        Patient("PTEST2", "Persistence Two", 45, "Test Condition B", 3));

    originalQueue.saveToFile(testFile);

    PatientQueue loadedQueue;

    loadedQueue.loadFromFile(testFile);

    Patient first = loadedQueue.dequeue();
    Patient second = loadedQueue.dequeue();

    check(first.getID() == "PTEST1",
        "Persistence restores first patient ID");

    check(first.getName() == "Persistence One",
        "Persistence restores first patient name");

    check(first.getAge() == 28,
        "Persistence restores first patient age");

    check(first.getCondition() == "Test Condition A",
        "Persistence restores first patient condition");

    check(first.getPriorityLevel() == 1,
        "Persistence restores first patient priority");

    check(second.getID() == "PTEST2",
        "Persistence restores second patient ID");

    check(second.getName() == "Persistence Two",
        "Persistence restores second patient name");

    check(second.getAge() == 45,
        "Persistence restores second patient age");

    check(second.getCondition() == "Test Condition B",
        "Persistence restores second patient condition");

    check(second.getPriorityLevel() == 3,
        "Persistence restores second patient priority");

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());
}

void testBackupRecovery()
{
    const string testFile = "test_recovery_data.txt";
    const string tempFile = testFile + ".tmp";
    const string backupFile = testFile + ".bak";

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());

    PatientQueue originalQueue;

    originalQueue.enqueue(
        Patient("R001", "Recovery Patient", 36, "Recovery Test", 2));

    originalQueue.saveToFile(testFile);

    std::rename(testFile.c_str(), backupFile.c_str());

    PatientQueue recoveredQueue;

    recoveredQueue.loadFromFile(testFile);

    Patient recoveredPatient = recoveredQueue.dequeue();

    check(recoveredPatient.getID() == "R001",
        "Backup recovery restores patient ID");

    check(recoveredPatient.getName() == "Recovery Patient",
        "Backup recovery restores patient name");

    check(recoveredPatient.getAge() == 36,
        "Backup recovery restores patient age");

    check(recoveredPatient.getCondition() == "Recovery Test",
        "Backup recovery restores patient condition");

    check(recoveredPatient.getPriorityLevel() == 2,
        "Backup recovery restores patient priority");

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());
}

void testMalformedRecordHandling()
{
    const string testFile = "test_malformed_data.txt";
    const string tempFile = testFile + ".tmp";
    const string backupFile = testFile + ".bak";

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());

    ofstream outFile(testFile);

    outFile << "V001|Valid First|25|Test Condition A|1" << endl;
    outFile << "BAD01|Broken Patient|notanumber|Broken Condition|2" << endl;
    outFile << "V002|Valid Second|40|Test Condition B|3" << endl;

    outFile.close();

    PatientQueue loadedQueue;

    loadedQueue.loadFromFile(testFile);

    Patient first = loadedQueue.dequeue();
    Patient second = loadedQueue.dequeue();
    Patient third = loadedQueue.dequeue();

    check(first.getID() == "V001",
        "Malformed loader keeps valid record before bad record");

    check(second.getID() == "V002",
        "Malformed loader continues after bad record");

    check(third.getID() == "0",
        "Malformed loader skips bad record instead of loading it");

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());
}

void testQueueReportGeneration()
{
    const string reportFile = "test_queue_report.txt";

    std::remove(reportFile.c_str());

    PatientQueue queue;

    queue.enqueue(
        Patient("S001", "Statistics One", 20, "Test", 1));

    queue.enqueue(
        Patient("S002", "Statistics Two", 40, "Test", 2));

    queue.enqueue(
        Patient("S003", "Statistics Three", 60, "Test", 3));

    queue.saveQueueReport(reportFile);

    ifstream inFile(reportFile);

    string reportContent;
    string line;

    while (getline(inFile, line))
    {
        reportContent += line + "\n";
    }

    inFile.close();

    check(reportContent.find("Total Patients: 3") != string::npos,
        "Queue report contains correct total patient count");

    check(reportContent.find("Critical (Priority 1): 1") != string::npos,
        "Queue report contains correct critical count");

    check(reportContent.find("Moderate (Priority 2): 1") != string::npos,
        "Queue report contains correct moderate count");

    check(reportContent.find("Stable (Priority 3): 1") != string::npos,
        "Queue report contains correct stable count");

    check(reportContent.find("Average Patient Age: 40.0") != string::npos,
        "Queue report contains correct average age");

    check(reportContent.find("Critical Percentage: 33.3%") != string::npos,
        "Queue report contains correct critical percentage");

    check(reportContent.find("Moderate Percentage: 33.3%") != string::npos,
        "Queue report contains correct moderate percentage");

    check(reportContent.find("Stable Percentage: 33.3%") != string::npos,
        "Queue report contains correct stable percentage");
}

void testDuplicateIDHandling()
{
    const string testFile = "test_duplicate_data.txt";
    const string tempFile = testFile + ".tmp";
    const string backupFile = testFile + ".bak";

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());

    ofstream outFile(testFile);

    outFile << "D001|Original Patient|25|Condition A|1" << endl;
    outFile << "D001|Duplicate Patient|40|Condition B|2" << endl;
    outFile << "D002|Second Valid Patient|50|Condition C|3" << endl;

    outFile.close();

    PatientQueue loadedQueue;

    loadedQueue.loadFromFile(testFile);

    Patient first = loadedQueue.dequeue();
    Patient second = loadedQueue.dequeue();
    Patient third = loadedQueue.dequeue();

    check(first.getID() == "D001",
        "Duplicate loader keeps first occurrence of patient ID");

    check(second.getID() == "D002",
        "Duplicate loader continues with next valid patient");

    check(third.getID() == "0",
        "Duplicate loader skips repeated patient ID");

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());
}

void testBackupPreservesPreviousVersion()
{
    const string testFile = "test_backup_version.txt";
    const string tempFile = testFile + ".tmp";
    const string backupFile = testFile + ".bak";

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());

    PatientQueue firstVersion;

    firstVersion.enqueue(
        Patient("B001", "Original Version", 30, "Version One", 2));

    firstVersion.saveToFile(testFile);

    PatientQueue secondVersion;

    secondVersion.enqueue(
        Patient("B001", "Original Version", 30, "Version One", 2));

    secondVersion.enqueue(
        Patient("B002", "New Patient", 40, "Version Two", 3));

    secondVersion.saveToFile(testFile);

    PatientQueue primaryQueue;
    primaryQueue.loadFromFile(testFile);

    Patient primaryFirst = primaryQueue.dequeue();
    Patient primarySecond = primaryQueue.dequeue();

    PatientQueue backupQueue;
    backupQueue.loadFromFile(backupFile);

    Patient backupFirst = backupQueue.dequeue();
    Patient backupSecond = backupQueue.dequeue();

    check(primaryFirst.getID() == "B001",
        "Latest primary keeps original patient");

    check(primarySecond.getID() == "B002",
        "Latest primary contains newly added patient");

    check(backupFirst.getID() == "B001",
        "Backup preserves previous version patient");

    check(backupSecond.getID() == "0",
        "Backup does not contain data added in latest version");

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());
}

void testEmptyQueueReport()
{
    const string reportFile = "test_empty_queue_report.txt";

    std::remove(reportFile.c_str());

    PatientQueue queue;

    queue.saveQueueReport(reportFile);

    ifstream inFile(reportFile);

    string reportContent;
    string line;

    while (getline(inFile, line))
    {
        reportContent += line + "\n";
    }

    inFile.close();

    check(reportContent.find("Total Patients: 0") != string::npos,
        "Empty queue report has zero total patients");

    check(reportContent.find("Critical (Priority 1): 0") != string::npos,
        "Empty queue report has zero critical patients");

    check(reportContent.find("Moderate (Priority 2): 0") != string::npos,
        "Empty queue report has zero moderate patients");

    check(reportContent.find("Stable (Priority 3): 0") != string::npos,
        "Empty queue report has zero stable patients");

    check(reportContent.find("Average Patient Age: 0.0") != string::npos,
        "Empty queue report has zero average age");

    check(reportContent.find("Critical Percentage: 0.0%") != string::npos,
        "Empty queue report has zero critical percentage");

    check(reportContent.find("Moderate Percentage: 0.0%") != string::npos,
        "Empty queue report has zero moderate percentage");

    check(reportContent.find("Stable Percentage: 0.0%") != string::npos,
        "Empty queue report has zero stable percentage");

    std::remove(reportFile.c_str());
}

void testOutOfRangeAndIncompleteRecords()
{
    const string testFile = "test_invalid_range_data.txt";
    const string tempFile = testFile + ".tmp";
    const string backupFile = testFile + ".bak";

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());

    ofstream outFile(testFile);

    outFile << "RNG001|Valid First|25|Condition A|1" << endl;
    outFile << "BADAGE|Invalid Age|999|Condition B|2" << endl;
    outFile << "BADPRI|Invalid Priority|30|Condition C|4" << endl;
    outFile << "INCOMPLETE|Missing Fields|30" << endl;
    outFile << "RNG002|Valid Second|50|Condition D|3" << endl;

    outFile.close();

    PatientQueue loadedQueue;

    loadedQueue.loadFromFile(testFile);

    Patient first = loadedQueue.dequeue();
    Patient second = loadedQueue.dequeue();
    Patient third = loadedQueue.dequeue();

    check(first.getID() == "RNG001",
        "Loader keeps valid record before invalid range records");

    check(second.getID() == "RNG002",
        "Loader continues after multiple invalid records");

    check(third.getID() == "0",
        "Loader skips out-of-range and incomplete records");

    std::remove(testFile.c_str());
    std::remove(tempFile.c_str());
    std::remove(backupFile.c_str());
}

int main()
{
    cout << "===== HOSPITAL SYSTEM AUTOMATED TESTS =====" << endl;

    testPatientModel();
    testPriorityOrdering();
    testEqualPriorityFIFO();
    testEmptyQueueDequeue();
    testMixedPriorityAndFIFO();
    testPersistenceRoundTrip();
    testBackupRecovery();
    testMalformedRecordHandling();
    testQueueReportGeneration();
    testDuplicateIDHandling();
    testBackupPreservesPreviousVersion();
    testEmptyQueueReport();
    testOutOfRangeAndIncompleteRecords();

    cout << "\nPassed: " << passedTests << endl;
    cout << "Failed: " << failedTests << endl;

    return failedTests == 0 ? 0 : 1;
}