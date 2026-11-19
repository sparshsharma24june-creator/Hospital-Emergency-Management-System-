#include <iostream>
using namespace std;

class Patient {
public:
    int id;
    char name[30];
    int age;
    char problem[30];
};

class Hospital {
public:
    Patient p[100];
    int pc = 0;

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

        cout << "Enter Age: ";
        cin >> p[pc].age;

        if (p[pc].age <= 0 || p[pc].age > 120) {
            cout << "Invalid age\n";
            return;
        }

        cout << "Enter Health Problem: ";
        cin >> p[pc].problem;

        pc++;

        cout << "Patient registered successfully\n";
    }

    void displayPatients() {
        if (pc == 0) {
            cout << "No patients registered\n";
            return;
        }

        for (int i = 0; i < pc; i++) {
            cout << "\nPatient ID: " << p[i].id;
            cout << "\nName: " << p[i].name;
            cout << "\nAge: " << p[i].age;
            cout << "\nProblem: " << p[i].problem;
            cout << "\n";
        }
    }

    void searchPatient() {
        int id;
        int found = 0;

        cout << "Enter Patient ID to search: ";
        cin >> id;

        for (int i = 0; i < pc; i++) {
            if (p[i].id == id) {
                cout << "\nPatient Found\n";
                cout << "ID: " << p[i].id << "\n";
                cout << "Name: " << p[i].name << "\n";
                cout << "Age: " << p[i].age << "\n";
                cout << "Problem: " << p[i].problem << "\n";

                found = 1;
                break;
            }
        }

        if (found == 0) {
            cout << "Patient not found\n";
        }
    }

    void menu() {
        int choice;

        do {
            cout << "\n===== PATIENT MANAGEMENT =====\n";
            cout << "1. Register Patient\n";
            cout << "2. Display Patients\n";
            cout << "3. Search Patient\n";
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
                    searchPatient();
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