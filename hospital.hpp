
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
    int height;

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

    Patient* insertAVL(Patient* root, Patient* newPatient);
    Patient* rightRotate(Patient* y);
    Patient* leftRotate(Patient* x);
    Patient* searchAVL(Patient* root, int id);
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
