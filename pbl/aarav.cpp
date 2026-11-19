#include <iostream>
using namespace std;

class Doctor {
public:
    int id;
    char name[30];
    char specialization[30];
    int available;
};

class Bed {
public:
    int id;
    char type[20];
    int occupied;
    int patientID;
};

class Hospital {
public:
    Doctor d[100];
    Bed b[100];

    int dc = 0;
    int bc = 0;

    void addDoctor() {
        int id;

        if (dc >= 100) {
            cout << "Doctor limit reached\n";
            return;
        }

        cout << "Enter Doctor ID: ";
        cin >> id;

        for (int i = 0; i < dc; i++) {
            if (d[i].id == id) {
                cout << "Doctor ID already exists\n";
                return;
            }
        }

        d[dc].id = id;

        cout << "Enter Doctor Name: ";
        cin >> d[dc].name;

        cout << "Enter Specialization: ";
        cin >> d[dc].specialization;

        d[dc].available = 1;
        dc++;

        cout << "Doctor added successfully\n";
    }

    void displayDoctors() {
        if (dc == 0) {
            cout << "No doctors available\n";
            return;
        }

        for (int i = 0; i < dc; i++) {
            cout << "\nDoctor ID: " << d[i].id;
            cout << "\nName: " << d[i].name;
            cout << "\nSpecialization: "
                 << d[i].specialization;

            if (d[i].available == 1)
                cout << "\nStatus: Available\n";
            else
                cout << "\nStatus: Busy\n";
        }
    }

    void addBed() {
        int id;

        if (bc >= 100) {
            cout << "Bed limit reached\n";
            return;
        }

        cout << "Enter Bed ID: ";
        cin >> id;

        for (int i = 0; i < bc; i++) {
            if (b[i].id == id) {
                cout << "Bed ID already exists\n";
                return;
            }
        }

        b[bc].id = id;

        cout << "Enter Bed Type (ICU/General): ";
        cin >> b[bc].type;

        b[bc].occupied = 0;
        b[bc].patientID = -1;
        bc++;

        cout << "Bed added successfully\n";
    }

    void displayBeds() {
        if (bc == 0) {
            cout << "No beds available\n";
            return;
        }

        for (int i = 0; i < bc; i++) {
            cout << "\nBed ID: " << b[i].id;
            cout << "\nBed Type: " << b[i].type;

            if (b[i].occupied == 1)
                cout << "\nStatus: Occupied\n";
            else
                cout << "\nStatus: Available\n";
        }
    }

    void menu() {
        int choice;

        do {
            cout << "\n===== HOSPITAL MANAGEMENT =====\n";
            cout << "1. Add Doctor\n";
            cout << "2. Display Doctors\n";
            cout << "3. Add Bed\n";
            cout << "4. Display Beds\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addDoctor();
                    break;

                case 2:
                    displayDoctors();
                    break;

                case 3:
                    addBed();
                    break;

                case 4:
                    displayBeds();
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