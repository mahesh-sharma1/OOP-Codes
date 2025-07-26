#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

// Base class
class Person
{
protected:
    string name;
    int age;
    string gender;

public:
    Person()
    {
        name = "";
        age = 0;
        gender = "";
    }

    Person(string n, int a, string g)
    {
        name = n;
        age = a;
        gender = g;
    }
    virtual void display()
    {
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender << endl;
    }
};

// Derived class: Patient
class Patient : public Person
{
private:
    string patientID;
    string disease;
    string visitDate;
    string prescription;

public:
    Patient()
    {
        patientID = "";
        disease = "";
        visitDate = "";
        prescription = "";
    }
    Patient(string id, string n, int a, string g, string d, string v, string p) : Person(n, a, g)
    {
        patientID = id;
        disease = d;
        visitDate = v;
        prescription = p;
    }

    void addRecord()
    {
        ofstream fout("patients.txt", ios::app);
        fout << patientID << "," << name << "," << age << "," << gender << ","
             << disease << "," << visitDate << "," << prescription << "\n";
        fout.close();
        cout << "Patient record added successfully.\n";
    }

    static void viewPatients()
    {
        ifstream fin("patients.txt");
        string line;
        cout << "\n--- Patient Records ---\n";
        while (getline(fin, line))
        {
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i] == ',')
                    line[i] = ' ';
            }
            cout << line << endl;
        }
        if (fin.eof())
        {
            cout << "End of records.\n";
        }

        fin.close();
    }

    static void searchPatient(string &searchID)
    {
        ifstream fin("patients.txt");
        string str;

        while (getline(fin, str))
        {
            if (str.substr(0, searchID.length()) == searchID)
            {
                cout << "\nPatient Found:\n";
                for (int i = 0; i < str.length(); ++i)
                {
                    if (str[i] == ',')
                        cout << ' ';
                    else
                        cout << str[i];
                }
                cout << endl;
                fin.close();
                return;
            }
        }

        fin.close();
        cout << "Patient ID not found.\n";
    }
};

// Derived class: Doctor
class Doctor : public Person
{
private:
    string doctorID;
    string specialization;

public:
    Doctor() {}
    Doctor(string id, string n, int a, string g, string s)
        : Person(n, a, g), doctorID(id), specialization(s) {}

    void assignPatient()
    {
        cout << "Doctor " << name << " is assigned to a patient.\n";
    }

    void display() override
    {
        Person::display();
        cout << "Doctor ID: " << doctorID << "\nSpecialization: " << specialization << endl;
    }

    void saveDoctor()
    {
        ofstream fout("doctors.txt", ios::app);
        fout << doctorID << "," << name << "," << age << "," << gender << "," << specialization << "\n";
        fout.close();
    }
};

// Menu-driven hospital system
void showMenu()
{
    cout << "\n--- Medical Patient Record System ---\n";
    cout << "1. Add New Patient\n";
    cout << "2. View All Patients\n";
    cout << "3. Search Patient by ID\n";
    cout << "4. Add Doctor Info\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    int choice;
    do
    {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string id, name, gender, disease, date, prescription;
            int age;
            cout << "Enter Patient ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Gender: ";
            getline(cin, gender);
            cout << "Enter Disease: ";
            getline(cin, disease);
            cout << "Enter Visit Date: ";
            getline(cin, date);
            cout << "Enter Prescription: ";
            getline(cin, prescription);

            Patient p(id, name, age, gender, disease, date, prescription);
            p.addRecord();
        }
        else if (choice == 2)
        {
            Patient::viewPatients();
        }
        else if (choice == 3)
        {
            string id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            Patient::searchPatient(id);
        }
        else if (choice == 4)
        {
            string id, name, gender, spec;
            int age;
            cout << "Enter Doctor ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Gender: ";
            getline(cin, gender);
            cout << "Enter Specialization: ";
            getline(cin, spec);

            Doctor d(id, name, age, gender, spec);
            d.saveDoctor();
            cout << "Doctor record saved.\n";
        }
    } while (choice != 5);

    cout << "Exiting program...\n";
    return 0;
}
