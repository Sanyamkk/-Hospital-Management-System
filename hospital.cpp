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

// Right rotation
Patient* HospitalManagementSystem::rightRotate(Patient* y) {
    Patient* x = y->left;
    Patient* T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(y->left ? y->left->height : 0, y->right ? y->right->height : 0);
    x->height = 1 + max(x->left ? x->left->height : 0, x->right ? x->right->height : 0);

    return x;
}

// Left rotation
Patient* HospitalManagementSystem::leftRotate(Patient* x) {
    Patient* y = x->right;
    Patient* T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(x->left ? x->left->height : 0, x->right ? x->right->height : 0);
    y->height = 1 + max(y->left ? y->left->height : 0, y->right ? y->right->height : 0);

    return y;
}

Patient* HospitalManagementSystem::insertAVL(Patient* node, Patient* newPatient) 
{
    if (node == NULL)
        return newPatient;

    // Normal BST insert
    if (newPatient->id < node->id)
        node->left = insertAVL(node->left, newPatient);
    else if (newPatient->id > node->id)
        node->right = insertAVL(node->right, newPatient);
    else
        return node; // duplicate IDs not allowed

    // Update height
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    node->height = 1 + max(leftHeight, rightHeight);

    // Balance factor
    int balance = leftHeight - rightHeight;

    // Left Left Case
    if (balance > 1 && newPatient->id < node->left->id)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && newPatient->id > node->right->id)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && newPatient->id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && newPatient->id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Patient* HospitalManagementSystem::searchAVL(Patient* root, int id) 
{
    if (root == NULL || root->id == id)
        return root;
    if (id < root->id)
        return searchAVL(root->left, id);
    return searchAVL(root->right, id);
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

    root = insertAVL(root, newPatient);
    cout << "\nPatient added successfully!";
    cout << "\nAssigned Patient ID: " << id << endl;
}
void HospitalManagementSystem::searchPatient(int id) 
{
    Patient* result = searchAVL(root, id);
    if (result !=NULL)
        displayPatient(result);
    else
        cout << "\nPatient not found!" << endl;
}
void HospitalManagementSystem::scheduleAppointment(int patientId, string time, string date) 
{
    if (searchAVL(root, patientId) != NULL) {
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
