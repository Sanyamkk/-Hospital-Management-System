#include "hospital.hpp"
Patient::Patient(int i, string n, int a, string d, string c) 
{
    id = i;
    name = n;
    age = a;
    disease = d;
    contact = c;
    next = NULL;
    left = NULL;
    right = NULL;
}
Appointment::Appointment(int id, string t, string d) 
{
    patientId = id;
    time = t;
    date = d;
}
HospitalManagementSystem::HospitalManagementSystem() 
{
    head = NULL;
    root = NULL;
    totalPatients = 0;
}

Patient* HospitalManagementSystem::insertBST(Patient* root, Patient* newPatient) 
{
    if (root == NULL)
        return newPatient;
    if (newPatient->id < root->id)
        root->left = insertBST(root->left, newPatient);
    else if (newPatient->id > root->id)
        root->right = insertBST(root->right, newPatient);
    return root;
}

Patient* HospitalManagementSystem::searchBST(Patient* root, int id) 
{
    if (root == NULL || root->id == id)
        return root;
    if (id < root->id)
        return searchBST(root->left, id);
    return searchBST(root->right, id);
}

void HospitalManagementSystem::inorderTraversal(Patient* root) 
{
    if (root != NULL) {
        inorderTraversal(root->left);
        displayPatient(root);
        inorderTraversal(root->right);
    }
}

void HospitalManagementSystem::displayPatient(Patient* patient) 
{
    cout << "\n--------------------------------";
    cout << "\nPatient ID: " << patient->id;
    cout << "\nName: " << patient->name;
    cout << "\nAge: " << patient->age;
    cout << "\nDisease: " << patient->disease;
    cout << "\nContact: " << patient->contact;
    cout << "\n--------------------------------\n";
}

void HospitalManagementSystem::addPatient(string name, int age, string disease, string contact) 
{
    totalPatients++;
    int id = totalPatients;
    Patient* newPatient = new Patient(id, name, age, disease, contact);
    if (head == NULL) 
    {
        head = newPatient;
    } else {
        Patient* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newPatient;
    }

    root = insertBST(root, newPatient);
    cout << "\nPatient added successfully!";
    cout << "\nAssigned Patient ID: " << id << endl;
}
void HospitalManagementSystem::searchPatient(int id) 
{
    Patient* result = searchBST(root, id);
    if (result !=NULL)
        displayPatient(result);
    else
        cout << "\nPatient not found!" << endl;
}
void HospitalManagementSystem::scheduleAppointment(int patientId, string time, string date) 
{
    if (searchBST(root, patientId) != NULL) {
        appointments.push(Appointment(patientId, time, date));
        cout << "\nAppointment scheduled successfully!" << endl;
    } else {
        cout << "\nPatient ID not found!" << endl;
    }
}
void HospitalManagementSystem::displayNextAppointment() 
{
    if (!appointments.empty()) {
        Appointment next = appointments.front();
        cout << "\nNext Appointment:";
        cout << "\nPatient ID: " << next.patientId;
        cout << "\nTime: " << next.time;
        cout << "\nDate: " << next.date << endl;
    } 
    else 
    {
        cout << "\nNo appointments in queue!" << endl;
    }
}
void HospitalManagementSystem::completeAppointment() 
{
    if (!appointments.empty()) 
    {
        appointments.pop();
        cout << "\nAppointment marked as completed!" << endl;
    } 
    else 
    {
        cout << "\nNo appointments in queue!" << endl;
    }
}

void HospitalManagementSystem::displayAllPatients() 
{
    cout << "\nAll Patients (Sorted by ID):";
    inorderTraversal(root);
}

void HospitalManagementSystem::saveToFile() 
{
    ofstream file("hospital_data.txt");
    Patient* temp = head;

    while (temp != NULL) {
        file << temp->id << ","
             << temp->name << ","
             << temp->age << ","
             << temp->disease << ","
             << temp->contact << "\n";
        temp = temp->next;
    }

    file.close();
    cout << "\nData saved to file successfully!" << endl;
}
