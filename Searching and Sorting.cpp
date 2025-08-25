 //Problem Statement::
 /*
 Consider a student database of SEIT class (at least 15 records). Database contains
 different fields of 
every student like Roll No, Name and SGPA.(array of structure)
 a) Design a roll call list, arrange list of students according to roll numbers in
 ascending order (Use 
Bubble Sort)
 b) Arrange list of students alphabetically. (Use Insertion sort)
 c) Arrange list of students to find out first ten toppers from a class. (Use Quick sort)
 d) Search students according to SGPA. If more than one student having same SGPA, then
 print list 
of all students having same SGPA.
 e) Search a particular student according to name using binary search without recursion.
 */





#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

// Function to swap two students
void swap(Student &a, Student &b) {
    Student temp = a;
    a = b;
    b = temp;
}

// Bubble Sort by Roll Number
void bubbleSortByRoll(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].rollNo > arr[j + 1].rollNo)
                swap(arr[j], arr[j + 1]);
}

// Insertion Sort by Name (Alphabetically)
void insertionSortByName(Student arr[], int n) {
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].name > key.name) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Partition function for Quick Sort by SGPA
int partition(Student arr[], int low, int high) {
    float pivot = arr[high].sgpa;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].sgpa > pivot) { // Descending order
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort by SGPA
void quickSortBySGPA(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortBySGPA(arr, low, pi - 1);
        quickSortBySGPA(arr, pi + 1, high);
    }
}

// Search students by SGPA
void searchBySGPA(Student arr[], int n, float sgpa) {
    bool found = false;
    cout << "Students with SGPA " << sgpa << ":\n";
    for (int i = 0; i < n; i++) {
        if (arr[i].sgpa == sgpa) {
            cout << arr[i].rollNo << "\t" << arr[i].name << "\t" << arr[i].sgpa << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No student found with SGPA " << sgpa << endl;
    }
}

// Binary Search by Name (Non-recursive)
void binarySearchByName(Student arr[], int n, string target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].name == target) {
            cout << "Student Found:\n";
            cout << arr[mid].rollNo << "\t" << arr[mid].name << "\t" << arr[mid].sgpa << endl;
            return;
        }
        if (arr[mid].name < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    cout << "Student " << target << " not found.\n";
}

// Display students
void displayStudents(Student arr[], int n) {
    cout << "RollNo\tName\tSGPA\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i].rollNo << "\t" << arr[i].name << "\t" << arr[i].sgpa << endl;
    }
}

int main() {
    const int n = 15; // At least 15 students
    Student students[n];

    // Input student details
    cout << "Enter details of " << n << " students (RollNo Name SGPA):\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ":\n";
        cout << "Roll Number: "; cin >> students[i].rollNo;
        cin.ignore();
        cout << "Name: "; getline(cin, students[i].name);
        cout << "SGPA: "; cin >> students[i].sgpa;
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Sort by Roll Number (Bubble Sort)\n";
        cout << "2. Sort by Name (Insertion Sort)\n";
        cout << "3. Top 10 Toppers (Quick Sort by SGPA)\n";
        cout << "4. Search by SGPA\n";
        cout << "5. Search by Name (Binary Search)\n";
        cout << "6. Display All Students\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                bubbleSortByRoll(students, n);
                cout << "Students sorted by Roll Number:\n";
                displayStudents(students, n);
                break;
            case 2:
                insertionSortByName(students, n);
                cout << "Students sorted alphabetically by Name:\n";
                displayStudents(students, n);
                break;
            case 3:
                quickSortBySGPA(students, 0, n - 1);
                cout << "Top 10 Toppers:\n";
                displayStudents(students, 10);
                break;
            case 4:
                float sgpa;
                cout << "Enter SGPA to search: ";
                cin >> sgpa;
                searchBySGPA(students, n, sgpa);
                break;
            case 5: {
                insertionSortByName(students, n); 
                string name;
                cout << "Enter Name to search: ";
                cin.ignore();
                getline(cin, name);
                binarySearchByName(students, n, name);
                break;
                    }
            case 6: {
                displayStudents(students, n);
                break;
                    }

            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
