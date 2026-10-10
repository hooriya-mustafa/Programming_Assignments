#include <iostream>
#include <string>
using namespace std;

struct PatientNode
{
    int patientID;
    string patientName;
    int priority;
    PatientNode* next;
};

class PriorityQueue
{
private:
    PatientNode* front;
    PatientNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void Add(PatientNode* patient)
    {
        patient->next = nullptr;

        if (front == nullptr)
        {
            front = patient;
            rear = patient;
        }
        else if (patient->priority < front->priority)
        {
            patient->next = front;
            front = patient;
        }
        else
        {
            PatientNode* current = front;

            while (current->next != nullptr &&
                   current->next->priority <= patient->priority)
            {
                current = current->next;
            }

            patient->next = current->next;
            current->next = patient;

            if (patient->next == nullptr)
                rear = patient;
        }

        count++;
    }

    PatientNode* Remove()
    {
        if (front == nullptr)
            return nullptr;

        PatientNode* patient = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        patient->next = nullptr;
        count--;

        return patient;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        PatientNode* current = front;

        if (current == nullptr)
        {
            cout << "No patients waiting.\n";
            return;
        }

        while (current != nullptr)
        {
            cout << "\nPatient ID: " << current->patientID;
            cout << "\nPatient Name: " << current->patientName;
            cout << "\nPriority: " << current->priority;
            cout << "\n----------------------\n";

            current = current->next;
        }
    }

    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            PatientNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

PatientNode* CreatePatient(int id, string name, int priority)
{
    PatientNode* patient = new PatientNode;

    patient->patientID = id;
    patient->patientName = name;
    patient->priority = priority;
    patient->next = nullptr;

    return patient;
}

int main()
{
    PriorityQueue patients;
    int choice;

    do
    {
        cout << "\n----- Hospital Patient System -----\n";
        cout << "1. Add Patient\n";
        cout << "2. Process Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id, priority;
            string name;

            cout << "Enter Patient ID: ";
            cin >> id;

            cout << "Enter Patient Name: ";
            getline(cin >> ws, name);

            cout << "Enter Priority (1-3): ";
            cin >> priority;

            if (priority < 1 || priority > 3)
            {
                cout << "Invalid priority!\n";
            }
            else
            {
                patients.Add(CreatePatient(id, name, priority));
                cout << "Patient added successfully.\n";
            }
        }
        else if (choice == 2)
        {
            PatientNode* patient = patients.Remove();

            if (patient == nullptr)
                cout << "No patients waiting.\n";
            else
            {
                cout << "Now processing: "
                     << patient->patientName << endl;
                cout << "Priority: " << patient->priority << endl;

                delete patient;
            }
        }
        else if (choice == 3)
        {
            patients.PrintQueue();
        }
        else if (choice == 4)
        {
            if (patients.IsEmpty())
                cout << "Queue is empty.\n";
            else if (patients.IsNotEmpty())
                cout << "Patients are waiting.\n";
        }
        else if (choice == 5)
        {
            cout << "Exiting program.\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
