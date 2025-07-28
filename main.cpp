#include<bits/stdc++.h>
#include "hospital.cpp"
using namespace std;

int main() 
{
    HospitalManagementSystem hospital;
    int choice;

    do 
    {
        cout << "\n=== Hospital Management System ===";
        cout << "\n1. Add New Patient";
        cout << "\n2. Search Patient";
        cout << "\n3. Schedule Appointment";
        cout << "\n4. Display Next Appointment";
        cout << "\n5. Complete Current Appointment";
        cout << "\n6. Display All Patients";
        cout << "\n7. Save Data to File";
        cout << "\n8. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                string name, disease, contact;
                int age;
                cout << "\nEnter patient details:";
                cout << "\nName: ";
                cin.ignore();
                getline(cin, name);
                cout << "Age: ";
                cin >> age;
                cout << "Disease: ";
                cin.ignore();
                getline(cin, disease);
                cout << "Contact: ";
                getline(cin, contact);
                hospital.addPatient(name, age, disease, contact);
                break;
            }
            case 2: 
            {
                int id;
                cout << "\nEnter Patient ID: ";
                cin >> id;
                hospital.searchPatient(id);
                break;
            }
            case 3: 
            {
                int id;
                string time, date;
                cout << "\nEnter Patient ID: ";
                cin >> id;
                cout << "Enter Time (HH:MM): ";
                cin >> time;
                cout << "Enter Date (DD/MM/YYYY): ";
                cin >> date;
                hospital.scheduleAppointment(id, time, date);
                break;
            }
            case 4:
                hospital.displayNextAppointment();
                break;
            case 5:
                hospital.completeAppointment();
                break;
            case 6:
                hospital.displayAllPatients();
                break;
            case 7:
                hospital.saveToFile();
                break;
            case 8:
                cout << "\nThank you for using Hospital Management System!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
