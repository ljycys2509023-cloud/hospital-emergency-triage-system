# Hospital Emergency Triage Management System

A C++ priority-based triage system built on a manually implemented singly linked list.  



## 📌 Project Overview
This project implements a **Hospital Emergency Triage Management System** in C++, using a manually managed singly linked list as the underlying priority queue structure.  
- **Pointer-based queue management**: Maintains node links and queue ordering through explicit pointer operations.  
- **Dynamic memory management**: Explicitly allocates and releases queue nodes through controlled `new`/`delete` operations.  
- **Priority-queue invariant design**: Preserves urgency ordering while maintaining FIFO behavior among patients with equal priority.  


---


## 🛠️ Core Features
- **Priority-based enqueue**
- **FIFO for equal-priority patients**
- **O(1) dequeue**
- **Patient ID search**
- **Nurse/Doctor RBAC**
- **File persistence**
- **Defensive parsing**
- **Login lockout protection**
- **Explicit resource cleanup**: Releases owned queue nodes through a custom destructor.  


---


## 🔄 Project Update: From Data Structure to Application System

### 📌 Motivation  
After completing the initial implementation of a singly linked list, I explored how fundamental data structures can be applied to real-world scenarios.

The hospital emergency department was chosen as a practical case study, where patient management requires both priority-based decision making and efficient queue 
handling. This led to the development of a hospital emergency triage and queue management system built on top of the original linked list structure.

This transition reflects a shift from academic exercise to application-oriented system design.  



### 🚀 What’s New in v3.5  

  - **Robust file loading** — Rejects malformed, incomplete, and invalid patient records without interrupting startup.  
  - **Unique patient IDs** — Prevents duplicate IDs during both file loading and new patient registration.  
  - **Strict input validation** — Rejects empty fields, reserved delimiters, malformed numeric input, and invalid ranges.  
  - **Per-account login lockout** — Applies a five-attempt threshold with a 30-second temporary lockout and automatic recovery.  



### 🧠 Design Insight

The system adopts a priority-based insertion strategy with a look-ahead approach (`temp->next`), ensuring:

- Correct ordering of patients based on urgency
- FIFO behavior for patients with equal priority
- Clean and maintainable pointer logic



### 🛠 System Evolution

- **v1.0** — Basic singly linked list implementation  
- **v2.0** — Hospital emergency triage & queue management system  
- **v3.0** — Security governance & Role-Based Access Control  
- **v3.1** — Robustness Patch: Advanced input validation & edge-case handling  
- **v3.2** — Security Hardening: DJB2-based credential hashing & role-based authentication  
- **v3.3** — Architectural Decoupling: Separated class declarations (`.h`) from implementations (`.cpp`) and strengthened input validation  
- **v3.4** — File I/O Persistence: Persistent queue storage and restoration through `patient.txt`  
- **v3.5** — Reliability & Security Hardening: Robust file validation, unique patient IDs, strict input parsing & per-account login lockout  



### 💡 Reflection

This project demonstrates how a foundational data structure can evolve into an application-oriented system through:

- Maintaining explicit queue invariants for priority ordering and FIFO behavior  
- Strengthening data integrity through defensive parsing and persistent storage  
- Extending a low-level linked-list implementation with authentication, RBAC, and reliability safeguards  


---


## ⚙️ Complexity Analysis

| Operation | Time Complexity | Space Complexity | Logical Context |
| :--- | :--- | :--- | :--- |
| `enqueue` | $O(n)$ | $O(1)$ | Maintains priority order during Nurse registration. |
| `dequeue` | $O(1)$ | $O(1)$ | Immediate patient retrieval for Doctor treatment. |
| `searchByID` | $O(n)$ | $O(1)$ | Linear traversal to retrieve specific records. |
| `displayQueue`| $O(n)$ | $O(1)$ | Full system state visualization. |
| `Cleanup/Exit`| $O(n)$ | $O(1)$ | Iterative deallocation of all owned queue nodes. |
| `getHash` | $O(k)$ | $O(1)$ | $k$ is the length of the input password string. |
| `Login` | $O(m + k)$ | $O(1)$ | $m$ is the number of accounts in the in-memory account store and $k$ is the password length. |


--- 


## 🛡️ System Safety, Security & Implementation Highlights

This project emphasizes explicit resource ownership, defensive input handling, and role-based access control:  
  - **Role-Based Access Control (RBAC)**: Separates Doctor and Nurse workflows according to permitted operations.  
  - **Action Isolation**: Restricts destructive queue operations, such as patient discharge via `dequeue()`, to the Doctor workflow.  
  - **Explicit Dynamic Allocation**: Uses `new` and `delete` to manually manage queue nodes.  
  - **Deterministic Cleanup**: The custom destructor iteratively releases all nodes owned by the queue.  
  - **Dangling Pointer Prevention**: Reassigns queue pointers before deleting removed nodes to avoid accessing released memory.  
  - **Edge-Case Handling**: Handles empty queues and malformed input without dereferencing invalid pointers.  



### 🛡 Robustness Enhancements

- **Strict input validation**: Rejects empty fields, reserved delimiters, malformed numeric values, and out-of-range inputs before they enter the system.  
- **Robust file recovery**: Validates persisted patient records individually and skips malformed, incomplete, or invalid entries without terminating startup.  
- **Unique patient identification**: Prevents duplicate patient IDs during both file restoration and new patient registration.  
- **Graceful empty-queue handling**: Safely handles `dequeue()`, display, and search operations when no patient records are available.  
- **Controlled shutdown**: Saves the current queue state before program termination and releases resources through the queue destructor.  
- **Educational credential hashing**: Uses DJB2-based hashing instead of plaintext password comparison for demonstration purposes; DJB2 is not intended for production-grade password security.  
- **Per-account login protection**: Tracks failed authentication attempts independently and applies a temporary 30-second lockout after five consecutive failures.  


---


## 🖥️ Example Output

### 1. Role-Based Login 

```text
#################### SYSTEM LOGIN ####################
Enter username or 'exit' to shut down: nurse1
Enter password: 123

[!] Login Successful! Welcome nurse1!
```



### 2. Nurse Workstation — Registration & Triage  

```text
-------------------- NURSE WORKSTATION --------------------
1. Display All Waiting Patients
2. Register New Patient Entry
3. Search Patient by ID
4. Logout
Selection: 1

============================== LIVE HOSPITAL QUEUE ==============================
Pos   Patient Name      ID          Condition                Status
--------------------------------------------------------------------------------
No.1  Ahmad             P001        Heart Attack             [CRITICAL]
No.2  Wong              P004        Head Injury              [CRITICAL]
No.3  John              P003        Severe Asthma            [MODERATE]
No.4  Zali              P005        Abdominal Pain           [MODERATE]
No.5  Siti              P002        Common Cold              [MILD]
No.6  Tan               P006        Skin Rash                [MILD]
No.7  Han               P007        Feel Sad                 [MILD]
================================================================================
```



### 3. Doctor Workstation — Treatment Workflow

```text
++++++++++++++++++++ DOCTOR INTERFACE ++++++++++++++++++++
1. Treat Next Patient
2. Preview Next in Line
3. View Full Queue
4. Logout
Selection: 1

******************** CALLING PATIENT ********************
Patient ID          : P001
Name                : Ahmad
Age                 : 25
Clinical Note       : Heart Attack
Priority Status     : CRITICAL (Immediate Attention)
```


---


## 🚀 How to Run

### 1. Prerequisites

- A C++17-compatible compiler such as MSVC, g++, or Clang  
- Visual Studio 2022 or later is recommended for Windows
- If used, `patient.txt` should be located in the program's working directory for persistent patient data



### 2. Compile the Source Files

Using `g++`:

```bash
g++ -std=c++17 main.cpp hospital_triage_system.cpp -o hospital_system
```



### 3. Execute the Binary

Run the compiled program to enter the role-based login interface.

Windows:

```bash
hospital_system.exe
```

Linux/macOS:

```bash
./hospital_system
```



### 4. File Persistence

The system uses `patient.txt` to store and restore patient queue records across program sessions.

- If `patient.txt` exists, previously saved patient records are loaded when the program starts.
- If `patient.txt` does not exist, the system initializes the default sample patient queue.
- Malformed, incomplete, or invalid records are skipped during loading without terminating the program.
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



### 5. Demo Accounts & Usage

Default demonstration accounts:

- **Nurse:** `nurse1` / `123`
- **Doctor:** `doc1` / `888`

Use the on-screen numerical menus to access role-specific operations.

Type `exit` at the main login screen to terminate the program safely.


---


## 🗺 Future Roadmap

Planned development before executable packaging includes:

- Unified input validation
- Reliable persistence and safer file updates
- Treatment history and audit logging
- Queue statistics and reporting
- C++ ownership and resource-management hardening
- Automated regression testing
- Reproducible build and release-readiness improvements