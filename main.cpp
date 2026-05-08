#include "Hospital.h"
#include<iostream> 
#include<string> 
#include<iomanip>
using namespace std;

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