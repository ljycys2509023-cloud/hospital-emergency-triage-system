# Hospital Emergency Triage Management System

A reliability-focused C++ hospital triage system featuring priority-based patient management, role-based access control, crash-recoverable persistence, automated regression testing, and reproducible release engineering.  


## 📌 Project Overview

This project implements a **Hospital Emergency Triage Management System** in C++, evolving from a manually implemented singly linked list into a reliability-focused application with persistent storage, access control, auditability, automated testing, and reproducible release engineering.

- **Custom priority queue**: Uses a manually managed singly linked list with explicit pointer operations and deterministic node ownership.
- **Priority and FIFO guarantees**: Preserves clinical urgency ordering while maintaining FIFO behavior among patients with equal priority.
- **Reliability and security controls**: Provides role-based access, strict input validation, crash-recoverable persistence, audit logging, and treatment history.
- **Engineering quality**: Includes queue statistics and reporting, automated regression tests, C++ ownership hardening, and a CMake / CTest / CPack release pipeline.


---


## 🛠 Core Features

- **Priority-based patient queue**: Serves higher-priority patients first while preserving FIFO order among patients with equal priority.
- **O(1) dequeue and patient lookup support**: Provides efficient front removal and patient retrieval by unique ID.
- **Role-based access control (RBAC)**: Separates Nurse and Doctor workflows with authenticated role-specific permissions.
- **Strict input validation**: Rejects malformed text fields, invalid numeric input, duplicate patient IDs, and out-of-range values.
- **Authentication hardening**: Uses hashed credential verification and per-account login lockout protection.
- **Crash-recoverable persistence**: Uses temporary-file writes, previous-version backups, rollback behavior, and startup backup recovery.
- **Robust file loading**: Isolates malformed, incomplete, duplicate, and out-of-range records without preventing valid records from loading.
- **Audit logging and treatment history**: Records security-relevant actions and completed patient treatments with timestamps.
- **Queue statistics and reporting**: Calculates patient counts, priority distributions, percentages, and average age, with exportable reports.
- **Explicit ownership management**: Centralizes linked-list cleanup, prevents unsafe queue copying, and maintains controlled `new` / `delete` ownership.
- **Automated regression testing**: Provides 65 runtime regression checks plus compile-time ownership assertions.
- **Reproducible build and release pipeline**: Uses CMake, CTest, and CPack to produce tested Windows x64 Release builds and distributable ZIP packages.


---


## 🔄 Project Evolution: From Data Structure to Reliable Application

### 📌 Motivation

The project began as an implementation of a singly linked list and gradually evolved into a complete hospital emergency triage application.

The hospital emergency department was chosen as a practical case study because patient management naturally requires priority-based decision making, deterministic queue behavior, persistent records, controlled access, and operational traceability.

Rather than replacing the original data-structure implementation, the system preserves the manually managed linked list as its core priority queue while progressively adding application-level reliability and software-engineering safeguards.

This evolution demonstrates how a fundamental data structure can serve as the foundation for a tested, maintainable, and release-ready C++ application.



### 🚀 What's New in v4.0

- **Crash-recoverable persistence** — Uses temporary-file writes, previous-version backups, rollback protection, and automatic startup recovery.
- **Audit logging and treatment history** — Records security-relevant actions and completed treatments with timestamps for traceability.
- **Queue statistics and reporting** — Provides patient counts, priority distributions, percentages, average age, and exportable queue reports.
- **C++ ownership hardening** — Centralizes linked-list cleanup, prevents unsafe queue copying, and strengthens explicit resource ownership.
- **Automated regression testing** — Adds 65 runtime regression checks together with compile-time ownership assertions.
- **Reproducible CMake build system** — Builds both the application and regression-test executable from a clean source tree.
- **CTest integration** — Executes the complete automated regression suite against the Release build.
- **Release packaging with CPack** — Produces a clean Windows x64 ZIP containing the executable, README, and license.



### 🧠 Design Insight

The triage queue is implemented as a manually managed singly linked list, allowing the system to explicitly control priority ordering, FIFO stability, and node ownership.

During insertion, the queue traverses using a look-ahead strategy (`temp->next`). Lower numerical priority values represent higher clinical urgency, while traversal across nodes with equal priority ensures that newly arriving patients are inserted after existing patients of the same priority.

This design provides:

- **Deterministic priority ordering** — Critical patients are positioned ahead of lower-priority patients.
- **Stable FIFO behavior** — Patients with equal priority are served in arrival order.
- **O(n) enqueue** — Insertion may require traversal of the linked list.
- **O(1) dequeue** — The highest-priority patient is always stored at the head of the queue.
- **Explicit ownership control** — Queue nodes are created and released through controlled dynamic-memory operations.



### 🛠 System Evolution

- **v1.0** — Basic singly linked list implementation  
- **v2.0** — Hospital emergency triage & queue management system  
- **v3.0** — Security governance & Role-Based Access Control  
- **v3.1** — Robustness Patch: Advanced input validation & edge-case handling  
- **v3.2** — Security Hardening: DJB2-based credential hashing & role-based authentication  
- **v3.3** — Architectural Decoupling: Separated class declarations (`.h`) from implementations (`.cpp`) and strengthened input validation  
- **v3.4** — File I/O Persistence: Persistent queue storage and restoration through `patient.txt`  
- **v3.5** — Reliability & Security Hardening: Robust file validation, unique patient IDs, strict input parsing & per-account login lockout  
- **v3.6** — Persistence Reliability: Unified validation, safer temporary-file replacement, previous-version backups, rollback protection, and startup recovery.
- **v3.7** — Auditability & Reporting: Added audit logging, treatment history, queue statistics, percentage analysis, and exportable reports.
- **v3.8** — Resource Safety & Regression Testing: Hardened C++ ownership semantics and introduced 65 runtime regression checks with compile-time ownership assertions.
- **v4.0** — Release Engineering: Added CMake-based reproducible builds, CTest integration, Release-mode verification, CPack packaging, and a distributable Windows x64 release.



### 💡 Reflection

This project demonstrates how a fundamental data structure can evolve into a progressively hardened software system through iterative engineering.

The most significant development was not simply adding more features, but improving the reliability of the system around its original linked-list core. Persistence recovery, defensive validation, explicit ownership management, auditability, automated regression testing, and reproducible release tooling were introduced without replacing the underlying priority-queue design.

The project reinforced several software-engineering principles:

- **Preserve clear invariants** — Priority ordering and FIFO behavior remain stable as the system grows.
- **Design for failure** — File corruption, invalid input, duplicate records, and interrupted persistence paths are handled defensively.
- **Protect behavior through testing** — Regression tests provide a repeatable safety net for future modifications.
- **Separate source from build artifacts** — CMake, CTest, and CPack make the application independently buildable, testable, and distributable.
- **Evolve incrementally** — Small, validated improvements reduced the risk of introducing regressions during long-term development.

The final result is a release-ready C++ application that connects data-structure fundamentals with practical software-engineering techniques.


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


## 🛡 System Safety, Security & Implementation Highlights

The system emphasizes explicit resource ownership, defensive data handling, controlled access, and recoverable persistence:

- **Role-Based Access Control (RBAC)**: Separates Nurse and Doctor workflows according to permitted operations.
- **Action isolation**: Restricts destructive queue operations, such as patient discharge through `dequeue()`, to the Doctor workflow.
- **Explicit dynamic allocation**: Uses `new` and `delete` to manually manage queue nodes.
- **Centralized cleanup**: All owned linked-list nodes are released through a dedicated `clear()` routine reused by the destructor.
- **Copy protection**: Copy construction and copy assignment are disabled for `PatientQueue` to prevent accidental shallow-copy ownership bugs.
- **Dangling-pointer prevention**: Queue pointers are reassigned before removed nodes are deleted, avoiding access to released memory.
- **Defensive edge-case handling**: Handles empty queues, malformed records, invalid ranges, and duplicate IDs without corrupting queue state.
- **Crash-recoverable persistence**: Uses temporary writes, previous-version backups, rollback behavior, and backup restoration when the primary data file is unavailable.
- **Authentication safeguards**: Uses hashed credential comparison and per-account temporary lockout after repeated failed login attempts.



### 🛡 Robustness Enhancements

- **Strict input validation**: Rejects empty fields, reserved delimiters, malformed numeric values, duplicate IDs, and out-of-range input before invalid data enters the system.
- **Fault-isolated file loading**: Validates persisted records individually and skips malformed, incomplete, duplicate, or out-of-range records while continuing to load valid data.
- **Crash-recoverable file updates**: Writes new queue state to a temporary file before replacing the primary file, preserves the previous version as a backup, and restores backup data when recovery is required.
- **Unique patient identification**: Prevents duplicate patient IDs during both file restoration and new patient registration.
- **Controlled shutdown**: Persists the current queue before program termination and releases owned queue resources deterministically.
- **Auditability**: Records security-relevant actions and completed treatment events with timestamps.
- **Resource-management hardening**: Centralizes linked-list cleanup and disables unsafe copying of `PatientQueue`.
- **Regression protection**: Uses 65 automated runtime checks plus compile-time ownership assertions to detect behavioral regressions.
- **Credential protection**: Uses DJB2-based hashing for demonstrative credential storage instead of plaintext password comparison.
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
4. View Queue Statistics
5. Save Queue Report
6. Logout
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
4. View Queue Statistics
5. Save Queue Report
6. Logout
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

To build the project from source:

- **CMake 3.20 or later**
- A **C++17-compatible compiler**
- On Windows, **Visual Studio 2022 with MSVC** is recommended
- A 64-bit Windows environment for reproducing the packaged Release build

The distributed Windows release package already includes `patient.txt`, so the application can load the bundled sample patient data immediately after extraction.



### 2. Configure and Build with CMake

From the project root directory, configure a 64-bit build:

```bash
cmake -S . -B build -A x64
```

Build the application and regression-test executable in Release mode:

```bash
cmake --build build --config Release
```

On Windows, the generated executables are located at:

```text
build/Release/hospital_system.exe
build/Release/hospital_tests.exe
```



### 3. Run the Application

After building from source, run the Release executable from the project root directory:

```bash
build\Release\hospital_system.exe
```

For the packaged Windows release, extract the ZIP archive and run:

```text
hospital_system.exe
```

Keep `patient.txt` in the same extracted directory as `hospital_system.exe` so the bundled sample patient data can be loaded correctly.

If both `patient.txt` and its backup are unavailable, the application initializes the built-in default patient queue and creates persistent data again during normal shutdown.



### 4. File Persistence and Recovery

The system uses `patient.txt` to preserve the patient queue across program sessions.

At startup:

- If `patient.txt` exists, valid patient records are loaded into the queue.
- Malformed, incomplete, duplicate, or out-of-range records are skipped individually without stopping the remaining valid records from loading.
- If `patient.txt` is unavailable but `patient.txt.bak` exists, the application attempts to restore the backup automatically.
- If neither the primary file nor its backup is available, the application initializes the built-in default patient queue.

During saving, the system uses a safer replacement strategy:

1. The current queue is first written to `patient.txt.tmp`.
2. The temporary file is flushed and finalized before the existing primary file is modified.
3. The previous `patient.txt` is preserved as `patient.txt.bak`.
4. The temporary file is renamed to become the new `patient.txt`.
5. If replacement fails, the previous backup is restored when possible.

The persistent record format is:

```text
PatientID|Name|Age|Condition|PriorityLevel
```

Example:

```text
P001|Ahmad|25|Heart Attack|1
P004|Wong|12|Head Injury|1
P003|John|60|Severe Asthma|2
```

The Windows release package includes a sample `patient.txt` file containing the initial patient dataset.



### 5. Demo Accounts & Usage

Default demonstration accounts:

- **Nurse:** `nurse1` / `123`
- **Doctor:** `doc1` / `888`

Use the on-screen numerical menus to access role-specific operations.

Type `exit` at the main login screen to terminate the program safely.



---



## 🧪 Automated Regression Testing

The project includes a dedicated automated regression suite in `tests/HospitalTests.cpp`.

The current suite provides:

- **65 runtime regression checks**
- **2 compile-time ownership assertions**
- Priority ordering and equal-priority FIFO verification
- Empty-queue and mixed-priority edge-case testing
- Persistence round-trip verification
- Backup recovery and previous-version preservation testing
- Malformed, incomplete, duplicate, and out-of-range record handling
- Queue statistics and report validation
- Empty-queue statistics boundary testing
- Compile-time protection against unsafe `PatientQueue` copying

After building the project in Release mode, run the complete regression suite through CTest:

```bash
ctest --test-dir build -C Release --output-on-failure
```

A successful run reports:

```text
100% tests passed, 0 tests failed out of 1
```

CTest executes the `hospital_tests` target, which contains the full runtime regression suite. The ownership assertions are validated during compilation.



---



## ✅ v4.0 Release Status

The original engineering roadmap has been completed.

- Unified input validation — Completed
- Reliable persistence and safer file updates — Completed
- Treatment history and audit logging — Completed
- Queue statistics and reporting — Completed
- C++ ownership and resource-management hardening — Completed
- Automated regression testing — Completed
- Reproducible build and release-readiness improvements — Completed

Version **v4.0** represents the completed console-based portfolio release, with reproducible CMake builds, automated regression testing through CTest, and Windows x64 packaging through CPack.