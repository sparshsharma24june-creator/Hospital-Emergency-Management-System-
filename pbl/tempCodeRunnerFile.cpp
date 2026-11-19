#include <iostream>
#include <string>
using namespace std;

struct Patient {
    int id, age, priority, bedNo, doctorId;
    string name, gender, contact, address, condition;
    bool admitted;
};
struct QueueNode {
    int patientId, priority;
    QueueNode* next;
};
struct Doctor {
    int id, assignedPatientId;
    string name, specialization;
    Doctor* next;
};
struct Treatment {
    int patientId;
    string diagnosis, medicine, doctorName;
};

class HEMS {
    Patient patients[100];
    int patientCount = 0, nextPatientId = 101;
    QueueNode* front = NULL;
    Doctor* doctorHead = NULL;
    int nextDoctorId = 1;
    bool beds[11] = {};
    Treatment history[100];
    int top = -1;

    int number(string msg, int low, int high) {
        int x;
        while (true) {
            cout << msg;
            if (cin >> x && x >= low && x <= high) {
                cin.ignore(1000, '\n');
                return x;
            }
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    string line(string msg) {
        string s;
        cout << msg;
        getline(cin, s);
        return s;
    }
    int patientIndex(int id) {
        for (int i = 0; i < patientCount; i++)
            if (patients[i].id == id) return i;
        return -1;
    }
    string priorityText(int p) {
        if (p == 1) return "Critical";
        if (p == 2) return "Serious";
        return "Normal";
    }
    string requiredSpecialization(string c) {
        if (c == "Heart Problem") return "Cardiologist";
        if (c == "Bone Injury") return "Orthopedic";
        if (c == "Breathing Problem") return "Pulmonologist";
        if (c == "Brain/Nerve Problem") return "Neurologist";
        return "General Physician";
    }
    Doctor* freeDoctor(string spec) {
        Doctor* d = doctorHead;
        while (d != NULL) {
            if (d->specialization == spec && d->assignedPatientId == 0)
                return d;
            d = d->next;
        }
        return NULL;
    }
    int freeBed() {
        for (int i = 1; i <= 10; i++)
            if (!beds[i]) return i;
        return 0;
    }
    void enqueue(int id, int priority) {
        QueueNode* n = new QueueNode{id, priority, NULL};
        if (front == NULL || priority < front->priority) {
            n->next = front;
            front = n;
            return;
        }
        QueueNode* t = front;
        while (t->next != NULL && t->next->priority <= priority)
            t = t->next;
        n->next = t->next;
        t->next = n;
    }
    void dequeue() {
        if (front != NULL) {
            QueueNode* t = front;
            front = front->next;
            delete t;
        }
    }
    void releaseResources(Patient& p) {
        Doctor* d = doctorHead;
        while (d != NULL) {
            if (d->id == p.doctorId) {
                d->assignedPatientId = 0;
                break;
            }
            d = d->next;
        }
        if (p.bedNo >= 1 && p.bedNo <= 10) beds[p.bedNo] = false;
        p.doctorId = 0;
        p.bedNo = 0;
        p.admitted = false;
    }

public:
    ~HEMS() {
        while (front != NULL) dequeue();
        while (doctorHead != NULL) {
            Doctor* t = doctorHead;
            doctorHead = doctorHead->next;
            delete t;
        }
    }


    void registerPatient() {
        if (patientCount == 100) {
            cout << "Patient record limit reached.\n";
            return;
        }
        Patient p;
        p.id = nextPatientId++;
        p.name = line("Enter patient name: ");
        p.age = number("Enter age: ", 1, 120);
        p.gender = line("Enter gender: ");
        p.contact = line("Enter contact number: ");
        p.address = line("Enter address: ");

        cout << "\n1. Heart Problem\n2. Bone Injury\n3. Fever/General Illness\n";
        cout << "4. Breathing Problem\n5. Brain/Nerve Problem\n";
        int c = number("Select condition: ", 1, 5);
        if (c == 1) p.condition = "Heart Problem";
        else if (c == 2) p.condition = "Bone Injury";
        else if (c == 3) p.condition = "Fever/General Illness";
        else if (c == 4) p.condition = "Breathing Problem";
        else p.condition = "Brain/Nerve Problem";

        cout << "\n1. Critical\n2. Serious\n3. Normal\n";
        p.priority = number("Select priority: ", 1, 3);
        p.admitted = false;
        p.bedNo = 0;
        p.doctorId = 0;
        patients[patientCount++] = p;
        enqueue(p.id, p.priority);
        cout << "Patient registered. Patient ID: " << p.id << "\n";
    }

    void displayPatients() {
        if (patientCount == 0) { cout << "No patient records.\n"; return; }
        for (int i = 0; i < patientCount; i++) {
            Patient p = patients[i];
            cout << "\nID: " << p.id << " | Name: " << p.name
                 << " | Age: " << p.age << " | Condition: " << p.condition
                 << " | Priority: " << priorityText(p.priority)
                 << " | Status: " << (p.admitted ? "Admitted" : "Waiting/Not admitted") << "\n";
        }
    }

    void searchPatient() {
        int id = number("Enter patient ID: ", 1, 1000000);
        int i = patientIndex(id);
        if (i == -1) { cout << "Patient not found.\n"; return; }
        Patient p = patients[i];
        cout << "\nID: " << p.id << "\nName: " << p.name
             << "\nAge: " << p.age << "\nGender: " << p.gender
             << "\nContact: " << p.contact << "\nAddress: " << p.address
             << "\nCondition: " << p.condition
             << "\nPriority: " << priorityText(p.priority)
             << "\nStatus: " << (p.admitted ? "Admitted" : "Not admitted") << "\n";
    }

   
    void displayQueue() {
        if (front == NULL) { cout << "Emergency queue is empty.\n"; return; }
        QueueNode* t = front;
        cout << "\nEmergency Queue (Critical first):\n";
        while (t != NULL) {
            int i = patientIndex(t->patientId);
            cout << "Patient ID: " << t->patientId << " | Priority: "
                 << priorityText(t->priority);
            if (i != -1) cout << " | Name: " << patients[i].name;
            cout << "\n";
            t = t->next;
        }
    }

    
    void addDoctor() {
        Doctor* d = new Doctor;
        d->id = nextDoctorId++;
        d->name = line("Enter doctor name: ");
        cout << "\n1. Cardiologist\n2. Orthopedic\n3. General Physician\n";
        cout << "4. Pulmonologist\n5. Neurologist\n";
        int c = number("Select specialization: ", 1, 5);
        if (c == 1) d->specialization = "Cardiologist";
        else if (c == 2) d->specialization = "Orthopedic";
        else if (c == 3) d->specialization = "General Physician";
        else if (c == 4) d->specialization = "Pulmonologist";
        else d->specialization = "Neurologist";
        d->assignedPatientId = 0;
        d->next = NULL;
        if (doctorHead == NULL) doctorHead = d;
        else {
            Doctor* t = doctorHead;
            while (t->next != NULL) t = t->next;
            t->next = d;
        }
        cout << "Doctor added. Doctor ID: " << d->id << "\n";
    }

    void displayDoctors() {
        if (doctorHead == NULL) { cout << "No doctors registered.\n"; return; }
        Doctor* d = doctorHead;
        while (d != NULL) {
            cout << "ID: " << d->id << " | " << d->name
                 << " | " << d->specialization << " | "
                 << (d->assignedPatientId == 0 ? "Available" : "Assigned") << "\n";
            d = d->next;
        }
    }

    void displayBeds() {
        cout << "\nBed Status:\n";
        for (int i = 1; i <= 10; i++)
            cout << "Bed " << i << ": " << (beds[i] ? "Occupied" : "Available") << "\n";
    }

    void admitNextPatient() {
        if (front == NULL) { cout << "No patient waiting.\n"; return; }
        int i = patientIndex(front->patientId);
        if (i == -1) { cout << "Patient record not found.\n"; return; }
        Patient& p = patients[i];
        string spec = requiredSpecialization(p.condition);
        Doctor* d = freeDoctor(spec);
        int bed = freeBed();
        if (d == NULL) {
            cout << "No available " << spec << ". Patient remains in queue.\n";
            return;
        }
        if (bed == 0) {
            cout << "No bed available. Patient remains in queue.\n";
            return;
        }
        d->assignedPatientId = p.id;
        beds[bed] = true;
        p.doctorId = d->id;
        p.bedNo = bed;
        p.admitted = true;
        dequeue();
        cout << "Patient admitted successfully.\nDoctor: " << d->name
             << "\nBed number: " << bed << "\n";
    }

    
    void addTreatment() {
        if (top == 99) { cout << "Treatment history is full.\n"; return; }
        int id = number("Enter admitted patient ID: ", 1, 1000000);
        int i = patientIndex(id);
        if (i == -1 || !patients[i].admitted) {
            cout << "Patient not found or not admitted.\n";
            return;
        }
        string doctorName = "Unknown";
        Doctor* d = doctorHead;
        while (d != NULL) {
            if (d->id == patients[i].doctorId) { doctorName = d->name; break; }
            d = d->next;
        }
        Treatment t;
        t.patientId = id;
        t.doctorName = doctorName;
        t.diagnosis = line("Enter diagnosis: ");
        t.medicine = line("Enter medicine/treatment: ");
        history[++top] = t;
        cout << "Treatment saved successfully.\n";
    }

    void viewTreatments() {
        if (top == -1) { cout << "No treatment records.\n"; return; }
        for (int i = top; i >= 0; i--)
            cout << "Patient ID: " << history[i].patientId
                 << " | Doctor: " << history[i].doctorName
                 << " | Diagnosis: " << history[i].diagnosis
                 << " | Medicine: " << history[i].medicine << "\n";
    }

    void dischargePatient() {
        int id = number("Enter patient ID to discharge: ", 1, 1000000);
        int i = patientIndex(id);
        if (i == -1 || !patients[i].admitted) {
            cout << "Patient not found or not admitted.\n";
            return;
        }
        int c = number("Confirm discharge? (1 = Yes, 2 = No): ", 1, 2);
        if (c == 1) {
            releaseResources(patients[i]);
            cout << "Patient discharged. Doctor and bed released.\n";
        } else cout << "Discharge cancelled.\n";
    }

    void menu() {
        int choice;
        do {
            cout << "\n===== HOSPITAL EMERGENCY MANAGEMENT SYSTEM =====\n";
            cout << "1. Register Patient\n2. View All Patients\n3. Search Patient\n";
            cout << "4. View Emergency Queue\n5. Add Doctor\n6. View Doctors\n";
            cout << "7. View Bed Status\n8. Admit Next Patient\n";
            cout << "9. Add Treatment\n10. View Treatment History\n";
            cout << "11. Discharge Patient\n0. Exit\n";
            choice = number("Enter choice: ", 0, 11);
            switch (choice) {
                case 1: registerPatient(); break;
                case 2: displayPatients(); break;
                case 3: searchPatient(); break;
                case 4: displayQueue(); break;
                case 5: addDoctor(); break;
                case 6: displayDoctors(); break;
                case 7: displayBeds(); break;
                case 8: admitNextPatient(); break;
                case 9: addTreatment(); break;
                case 10: viewTreatments(); break;
                case 11: dischargePatient(); break;
                case 0: cout << "Thank you for using HEMS.\n"; break;
            }
        } while (choice != 0);
    }
};

int main() {
    HEMS hospital;
    hospital.menu();
    return 0;
}