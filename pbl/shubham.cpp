#include <iostream>
using namespace std;

class Patient {
public:
    int id;
    char name[30];
    int treated;
    int discharged;
};

class Hospital {
public:
    Patient p[100];
    int pc;

    Hospital() {
        pc = 0;
    }

    void addPatient() {
        int id;

        if (pc >= 100) {
            cout << "Patient limit reached\n";
            return;
        }

        cout << "Enter Patient ID: ";
        cin >> id;

        if (id <= 0) {
            cout << "Invalid Patient ID\n";
            return;
        }

        for (int i = 0; i < pc; i++) {
            if (p[i].id == id) {
                cout << "Patient ID already exists\n";
                return;
            }
        }

        p[pc].id = id;

        cout << "Enter Patient Name: ";
        cin >> p[pc].name;

        p[pc].treated = 0;
        p[pc].discharged = 0;
        pc++;

        cout << "Patient added successfully\n";
    }

    void displayPatients() {
        if (pc == 0) {
            cout << "No patients found\n";
            return;
        }

        for (int i = 0; i < pc; i++) {
            cout << "\nPatient ID: " << p[i].id;
            cout << "\nName: " << p[i].name;

            if (p[i].discharged == 1)
                cout << "\nStatus: Discharged\n";
            else if (p[i].treated == 1)
                cout << "\nStatus: Treatment Complete\n";
            else
                cout << "\nStatus: Under Treatment\n";
        }
    }

    void completeTreatment() {
        int id;
        int found = -1;

        cout << "Enter Patient ID: ";
        cin >> id;

        for (int i = 0; i < pc; i++) {
            if (p[i].id == id) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            cout << "Patient not found\n";
            return;
        }

        if (p[found].discharged == 1) {
            cout << "Patient already discharged\n";
            return;
        }

        p[found].treated = 1;
        cout << "Treatment completed\n";
    }

    void dischargePatient() {
        int id;
        int found = -1;

        cout << "Enter Patient ID: ";
        cin >> id;

        for (int i = 0; i < pc; i++) {
            if (p[i].id == id) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            cout << "Patient not found\n";
            return;
        }

        if (p[found].treated == 0) {
            cout << "Complete treatment first\n";
            return;
        }

        if (p[found].discharged == 1) {
            cout << "Patient already discharged\n";
            return;
        }

        p[found].discharged = 1;
        cout << "Patient discharged successfully\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n===== TREATMENT MANAGEMENT =====\n";
            cout << "1. Add Patient\n";
            cout << "2. Display Patients\n";
            cout << "3. Complete Treatment\n";
            cout << "4. Discharge Patient\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input\n";
                cin.clear();
                cin.ignore(1000, '\n');
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1:
                    addPatient();
                    break;

                case 2:
                    displayPatients();
                    break;

                case 3:
                    completeTreatment();
                    break;

                case 4:
                    dischargePatient();
                    break;

                case 0:
                    cout << "Program closed\n";
                    break;

                default:
                    cout << "Invalid choice\n";
            }

        } while (choice != 0);
    }
};

int main() {
    Hospital h;
    h.menu();

    return 0;
}