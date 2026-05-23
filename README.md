# Singly Linked List Implementation in C++
## 📌 Project Overview
This project implements a **Singly Linked List** in C++, developed during my first year at XMUM. It focuses on building a solid understanding of: 
- **Pointer manipulation**: Managing links between nodes. 
- **Dynamic memory management**: Efficiently using heap memory.
- **Fundamental data structure design**: Principles of linear data structures. *These concepts are essential for low-level programming, system architecture, and cybersecurity.* 
---
## 🛠️ Core Features
- **Insert at Head**: (`addhead`) — $O(1)$ - **Insert after Value** (`addNode`) — $O(n)$ - **Delete by Value** (`delNode`) — $O(n)$ - **Traversal**: Print the list to 
console.  
- **Memory Safety**: Automatic cleanup via custom destructor. ---

## 🔄 Project Update: From Data Structure to Application System

📌 Motivation
After completing the initial implementation of a singly linked list, I explored how fundamental data structures can be applied to real-world scenarios.

The hospital emergency department was chosen as a practical case study, where patient management requires both priority-based decision making and efficient queue 
handling. This led to the development of a hospital emergency triage and queue management system built on top of the original linked list structure.

This transition reflects a shift from academic exercise to application-oriented system design.

---

🚀 What’s New in This Update

This version extends the original linked list into a functional system:  
	•	Introduced a Patient class to encapsulate structured data (ID, name, condition, priority level)  
	•	Transformed the linked list into a priority-based queue (triage system)  
	•	Implemented priority-aware insertion (enqueue) ensuring critical patients are served first  
	•	Added dequeue operation to simulate patient service workflow  
	•	Developed search functionality for locating patients by ID  
	•	Enhanced output formatting using <iomanip> for clear and professional display  
	•	Strengthened robustness with proper handling of edge cases (e.g., empty queue operations)  
	Dual-Role Workflow & RBAC 👥---Implemented a secure authentication layer that bifurcates system access into Doctor and Nurse workstations.  
	Advanced Patient Profiling 📊---Enhanced data objects to include Clinical Conditions and Age, allowing for a more holistic triage process.  
	Defensive Input Handling 🛡️---Integrated buffer management (cin.clear()/cin.ignore()) to protect the system from malformed user input and logical deadlocks.  
	• (V3.1)🛡️ Granular Input Sanitization: Implemented range-based validation for patient telemetry (e.g., Age constrained between 0-150) and robust buffer management to prevent infinite loops caused by type-mismatching inputs.  
	• (V3.2)🛡️ DJB2 hash-based authentication: Integrated DJB2 hash-based authentication and Role-Based Access Control (RBAC) to secure the medical workstation, alongside enhanced input validation logic to ensure clinical data integrity.  
	• (V3.3) The Architectural Refinement: Successfully migrated to a modular OOP architecture with separated interface (.h) and implementation (.cpp), while significantly enhancing system stability by implementing robust std::cin exception handling and resolving memory initialization warnings  
	• (V3.4)(current) File I/O Persistence Update: Before this update, all patient records existed only during runtime. After the program terminated, the queue was lost. With file I/O persistence, the system can now save and recover patient data, making it closer to a real-world hospital workflow.  
		- Added `saveToFile()` to store patient queue records into `patient.txt`.  
		- Added `loadFromFile()` to restore patient records when the program starts.  
		- Preserved priority-based triage ordering by reloading records through the existing `enqueue()` logic.  
		- Improved system continuity across multiple sessions.  

---

🧠 Design Insight

The system adopts a priority-based insertion strategy with a look-ahead approach (temp->next), ensuring:  
	•	Correct ordering of patients based on urgency  
	•	FIFO behavior for patients with equal priority  
	•	Clean and maintainable pointer logic  

---

🛠 System Evolution

	•	v1.0 — Basic singly linked list implementation  
	•	v2.0 — Hospital emergency triage & queue management system  
	•	v3.0 — Security Governance & Role-Based Access Update  
	•		v3.1 — Robustness Patch: Advanced Input Validation & Edge Case Handling  
	•		v3.2 — Security Hardening: DJB2 One-Way Hashing & Pre-seeded Authentication Database  
	•		v3.2 — Security Hardening: DJB2 One-Way Hashing & Pre-seeded Authentication Database  
	•		v3.3 — Architectural Decoupling: Separating class declarations (.h) from logic implementations & Enhanced Input Validation and Sanitization  
	•		v3.4 — File I/O Persistence Update: Add patient information storing in file function  

---

💡 Reflection

This update demonstrates how foundational data structures can evolve into meaningful applications. It also highlights the importance of:  
	•	Designing for real-world constraints  
	•	Writing maintainable and extensible code  
	•	Bridging the gap between theory and practical systems  

---

✅ Fulfilled Improvements

This update successfully implements several features that were previously outlined in the Future Improvements section of the initial linked list project.  

- ✔️ Search Functionality (`searchByID`)  
  → Enables efficient lookup of patients within the queue system.  

- ✔️ Application-Level Extension  
  → The original linked list has been extended into a practical hospital triage queue, demonstrating real-world applicability.  

- ✔️ Improved System Structure  
  → Clear separation between the data model (`Patient`), node structure, and queue logic (`PatientQueue`).  

- ✔️ Defensive Input Validation  
  → Uses `cin.clear()` and `cin.ignore()` to handle malformed user input and prevent logic hangs.  

- ✔️ Role-Based Access Control  
  → Separates Nurse and Doctor workstations, ensuring different users can only access appropriate operations.  

- ✔️ Educational Password Hashing  
  → Implements DJB2-based password hashing to avoid direct plaintext password comparison in the login system.  

- ✔️ File I/O Persistence  
  → Adds `saveToFile()` and `loadFromFile()` to store and restore patient queue records through `patient.txt`.  

---

🔄 Updated Future Improvements

With the core system now functional, future development will focus on:  
	•	🔹 Additional utility functions (e.g., reverse, statistics, or reporting features)  


## ⚙️ Complexity Analysis

| Operation | Time Complexity | Space Complexity | Logical Context |
| :--- | :--- | :--- | :--- |
| `enqueue` | $O(n)$ | $O(1)$ | Maintains priority order during Nurse registration. |
| `dequeue` | $O(1)$ | $O(1)$ | Immediate patient retrieval for Doctor treatment. |
| `searchByID` | $O(n)$ | $O(1)$ | Linear traversal to retrieve specific records. |
| `displayQueue`| $O(n)$ | $O(1)$ | Full system state visualization. |
| `Cleanup/Exit`| $O(n)$ | $O(1)$ | Recursive deallocation of all heap nodes. |
| `getHash` | $O(k)$ | $O(1)$ | $k$ is the length of the input password string. |
| `Login` | $O(m)$ | $O(1)$ | $m$ is the number of pre-seeded accounts in the database. |


--- 
## 🧠 System Safety, Security & Implementation Highlights🛡️ This project emphasizes safe and correct memory handling:
 - **Role-Based Access Control (RBAC**: Implemented a bifurcated interface for Doctors and Nurses. By segregating functional logic, the system ensures the Principle of Least Privilege (PoLP).
 - **Action Isolation**: Destructive operations (e.g., patient discharge via dequeue) are restricted to the Doctor’s workstation, preventing unauthorized data removal by triage staff.
 - **Explicit Dynamic Allocation**: Uses `new` and `delete` to manually manage heap memory. 
 - **Destructor for Full Cleanup**: All nodes are properly deallocated when the list object is destroyed, ensuring zero memory leaks. Guarantees 100% heap deallocation even during multi-role session switching.
 - **Dangling Pointer Prevention**: Careful re-assignment of pointers during deletion to avoid unsafe memory access.
 - **Edge Case Handling**:
  - Empty list verification.
  - Head node removal.
  - Safe traversal with `nullptr` termination. ---
 - **Cryptographic Credential Protection**: Utilizes the DJB2 hashing algorithm for one-way password encryption. This prevents sensitive data exposure even if the system's memory structure is inspected.  
 - **Pre-seeded Secure Database**: Initialized with structured administrative accounts, simulating a real-world multi-user environment.  



### 🛡 Robustness Enhancements
	• Input Sanitization: Integrated cin.clear() and cin.ignore() to neutralize buffer redundancy. This defensive layer shields the system from logic hangs or infinite loops caused by malformed user input. 
	• Secure Termination: Added a dedicated exit protocol that triggers the class destructor, ensuring a Graceful Shutdown rather than an abrupt process kill.
	- Safe handling of empty queue operations (dequeue, display, peek) 
	- Graceful error messages instead of runtime crashes
	- Defensive programming against invalid state access
	• (V3.1)Boundary Validation: Integrated logical checks for numerical inputs to ensure data integrity at the point of entry.
	• (V3.2)Cryptographic Integrity: Integrated DJB2 hashing algorithm to ensure administrative passwords are never stored in plaintext, mitigating memory-leak exploitation risks.
	• (V3.3)Input Validation: Implemented Robust Input Error Handling  

## ▶️ Example Output
### 🖥️ Example Output

**1. Multi-Role Secure Login (Hash-Verified)**  
```text
#################### SYSTEM LOGIN ####################
Enter username or 'exit' to shut down: nurse1
Enter password: 123

[!] Login Successful! Welcome nurse1!
```

**2. Nurse Workstation (Registration & Triage)**  

```text
-------------------- NURSE WORKSTATION --------------------
1. Display All Waiting Patients
2. Register New Patient Entry
3. Search Patient by ID
4. Logout
Selection: 1

1. 
//The output now features optimized spacing and includes clinical notes for better triage visibility:
============================== LIVE HOSPITAL QUEUE ==============================
Pos   Patient Name      ID          Condition                Status
--------------------------------------------------------------------------------
No.1  Wong              P004        Head Injury              [CRITICAL]
No.2  Ahmad             P001        Heart Attack             [CRITICAL]
No.3  John              P003        Severe Asthma            [MODERATE]
No.4  Zali              P005        Abdominal Pain           [MODERATE]
No.5  Siti              P002        Common Cold              [MILD]
No.6  Tan               P006        Skin Rash                [MILD]
================================================================================
```

**3. Doctor Interface (Treatment Workflow)**  
```text
++++++++++++++++++++ DOCTOR INTERFACE ++++++++++++++++++++
1. Treat Next Patient
2. Preview Next in Line
3. Logout
Selection: 1

******************** CALLING PATIENT ********************
Patient ID          : P004
Name                : Wong
Age                 : 12
Clinical Note       : Head Injury
Priority Status     : CRITICAL (Immediate Attention)
```


## 🚀 How to Run
````md
### 1. Prerequisites

Ensure you have a C++ compiler installed (e.g., `g++` for Linux/macOS or `MinGW` for Windows).  

This project also uses standard C++ file I/O through `<fstream>` to save and load patient records.  

### 2. Compile the Source File

Since the project is now modularized, you need to compile all .cpp files together:  
```bash
g++ main.cpp hospital_triage_system.cpp -o hospital_system
```
(Note: Ensure Hospital.h is in the same directory before compiling.)

### 3. Execute the Binary

Run the compiled program to enter the secure login interface

- Windows: hospital_system.exe  
- Linux/macOS: ./hospital_system  

### 4. File Persistence
The system automatically uses `patient.txt` to store and restore patient queue records.  

- If `patient.txt` exists, the system loads previous patient records when the program starts.  
- If `patient.txt` does not exist, the system initializes the default sample patient queue.  
- When the user exits from the main login screen by typing `exit`, the current queue is saved back to `patient.txt`.  

The saved patient records follow this format:  

```text
PatientID|Name|Age|Condition|PriorityLevel
```

Example:  

```text
P001|Ahmad|25|Heart Attack|1
P002|Siti|40|Common Cold|3
```

### 5. System Usage Guide

- Login as Nurse: use `nurse1` with password `123`.
- Login as Doctor: use `doc1` with password `888`.
- Navigation: Follow the on-screen numerical menus to perform operations.
- Termination: Type `exit` in the main login screen to trigger the secure exit protocol, save the current queue to `patient.txt`, and release allocated memory.

````

---

📈 v3.0 Evolution Summary
• Fulfilled:  
	✅ Role-based Access Control (RBAC)  
	✅ Clinical Condition Tracking  
	✅ Defensive Input Handling.  
• Security Update (v3.2):  
	🔐 Cryptographic Identity : Successfully transitioned from plaintext checks to DJB2 One-Way Hashing for administrative credential protection.  
• Structural Optimization (v3.3): Architectural Decoupling: Separated class declarations (.h) from implementations (.cpp) and enhanced input validation to prevent system instability.  
• File I/O Persistence Update (v3.4): This update introduces file-based persistence for the hospital emergency triage system.  
• Future Roadmap:  
	🛡️ Brute-force Protection for login attempts.  
