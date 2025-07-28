
#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include<bits/stdc++.h>
using namespace std;
struct Patient 
{
    int id;
    string name;
    int age;
    string disease;
    string contact;
    Patient* next;  
    Patient* left;  
    Patient* right;

    Patient(int i, string n, int a, string d, string c);
};

struct Appointment 
{
    int patientId;
    string time;
    string date;

    Appointment(int id, string t, string d);
};

class HospitalManagementSystem 
{
private:
    Patient* head;      
    Patient* root;     
    queue<Appointment> appointments;
    int totalPatients;

    Patient* insertBST(Patient* root, Patient* newPatient);
    Patient* searchBST(Patient* root, int id);
    void inorderTraversal(Patient* root);
    void displayPatient(Patient* patient);

public:
    HospitalManagementSystem();

    void addPatient(string name, int age, string disease, string contact);
    void searchPatient(int id);
    void scheduleAppointment(int patientId, string time, string date);
    void displayNextAppointment();
    void completeAppointment();
    void displayAllPatients();
    void saveToFile();
};

#endif
