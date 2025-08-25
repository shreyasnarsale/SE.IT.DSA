//Problem Statement:- 
/*Department maintains student’s database. The file contains roll number, name, division and 
address.  Write a program to create a sequential file to store and maintain student data. It should 
allow the user to add, delete information of student. Display information of particular student. If 
record of student does not exist an appropriate message is displayed. If student record is found it 
should display the student details. 
*/ 



#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
private:
    int roll_no;
    char name[50];
    char division[5];
    char address[100];

public:
    void accept() {
        cout << "Enter Roll Number: ";
        while (!(cin >> roll_no) || roll_no <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Roll Number. Enter again: ";
        }
        cin.ignore(); // remove newline
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Division: ";
        cin.getline(division, 5);
        cout << "Enter Address: ";
        cin.getline(address, 100);
    }

    void display() const {
        cout << roll_no << "\t" << name << "\t" << division << "\t" << address << endl;
    }

    int getRollNo() const {
        return roll_no;
    }
};

// Create database
void createDatabase() {
    int n;
    cout << "How many students do you want to add? ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid number. Enter again: ";
    }
    cin.ignore();

    ofstream outFile("Student.dat", ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot create file." << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << " details:\n";
        Student s;
        s.accept();
        outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    }
    outFile.close();
    cout << "\nDatabase created successfully.\n";
}

// Display all students
void displayDatabase() {
    ifstream inFile("Student.dat", ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    Student s;
    cout << "Roll\tName\tDivision\tAddress\n";
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
    }
    inFile.close();
}

// Add a single record
void addRecord() {
    ofstream outFile("Student.dat", ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    Student s;
    s.accept();
    outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    outFile.close();
    cout << "\nRecord added successfully.\n";
}

// Search for a student by roll number
void searchRecord() {
    ifstream inFile("Student.dat", ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    int roll;
    cout << "Enter Roll Number to search: ";
    while (!(cin >> roll) || roll <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Roll Number. Enter again: ";
    }

    Student s;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRollNo() == roll) {
            cout << "\nRecord Found:\n";
            cout << "Roll\tName\tDivision\tAddress\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";

    inFile.close();
}

// Delete a student record by roll number
void deleteRecord() {
    ifstream inFile("Student.dat", ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    ofstream outFile("Temp.dat", ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot create temporary file." << endl;
        inFile.close();
        return;
    }

    int roll;
    cout << "Enter Roll Number to delete: ";
    while (!(cin >> roll) || roll <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Roll Number. Enter again: ";
    }

    Student s;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRollNo() != roll) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("Student.dat");
    rename("Temp.dat", "Student.dat");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\nStudent Database Menu:\n";
        cout << "1. Create Database\n2. Display All Records\n3. Add Record\n4. Search Record\n5. Delete Record\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // remove newline

        switch (choice) {
            case 1: createDatabase(); break;
            case 2: displayDatabase(); break;
            case 3: addRecord(); break;
            case 4: searchRecord(); break;
            case 5: deleteRecord(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
