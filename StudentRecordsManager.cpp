#include <iostream>
using namespace std;

struct student {
    int roll_no;
    char name[50];
    float SGPA;
};

// Function to compare names
int compareNames(char a[], char b[]) {
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0') {
        if(a[i] != b[i])
            return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

// Accept student data
void accept(student list[], int n) {
    for(int i = 0; i < n; i++) {
        cout << "Enter Roll No, Name, SGPA of student " << i+1 << ": ";
        cin >> list[i].roll_no >> list[i].name >> list[i].SGPA;
    }
}

// Display student data in table format
void display(student list[], int n) {
    cout << "\nRoll No\tName\tSGPA\n";
    cout << "-------------------------\n";
    for(int i = 0; i < n; i++) {
        cout << list[i].roll_no << "\t" << list[i].name << "\t" << list[i].SGPA << "\n";
    }
}

// Bubble Sort by Roll No
void bubble_sort(student list[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-1-i; j++) {
            if(list[j].roll_no > list[j+1].roll_no) {
                student temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

// Insertion Sort by Roll No
void insert_sort(student list[], int n) {
    for(int k = 1; k < n; k++) {
        student key = list[k];
        int j = k - 1;
        while(j >= 0 && list[j].roll_no > key.roll_no) {
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = key;
    }
}

// Quick Sort by Roll No
void quick_sort(student list[], int first, int last) {
    if(first < last) {
        int pivot = first;
        int i = first, j = last;
        while(i < j) {
            while(list[i].roll_no <= list[pivot].roll_no && i < last)
                i++;
            while(list[j].roll_no > list[pivot].roll_no)
                j--;
            if(i < j) {
                student temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
        student temp = list[pivot];
        list[pivot] = list[j];
        list[j] = temp;

        quick_sort(list, first, j-1);
        quick_sort(list, j+1, last);
    }
}

// Search by SGPA
void search(student list[], int n) {
    float sgpa;
    cout << "Enter SGPA to search: ";
    cin >> sgpa;
    cout << "\nRoll No\tName\tSGPA\n";
    cout << "-------------------------\n";
    for(int i = 0; i < n; i++) {
        if(list[i].SGPA >= sgpa) {
            cout << list[i].roll_no << "\t" << list[i].name << "\t" << list[i].SGPA << "\n";
        }
    }
}

// Binary Search by Name
void binary_search(student list[], int n) {
    char searchName[50];
    cout << "Enter Name to search: ";
    cin >> searchName;

    // Sort by Name first
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-1-i; j++) {
            if(compareNames(list[j].name, list[j+1].name) > 0) {
                student temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }

    int lower = 0, upper = n-1, mid;
    bool found = false;
    while(lower <= upper) {
        mid = (lower + upper)/2;
        int cmp = compareNames(list[mid].name, searchName);
        if(cmp == 0) {
            cout << "Found: Roll No: " << list[mid].roll_no << ", SGPA: " << list[mid].SGPA << "\n";
            found = true;
            break;
        } else if(cmp < 0)
            lower = mid + 1;
        else
            upper = mid - 1;
    }
    if(!found) cout << "Name not found.\n";
}

// Display top 10 students by SGPA
void top_students(student list[], int n) {
    // Sort by SGPA descending
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-1-i; j++) {
            if(list[j].SGPA < list[j+1].SGPA) {
                student temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }

    int limit = (n < 10) ? n : 10;
    cout << "\nTop " << limit << " students:\n";
    cout << "Roll No\tName\tSGPA\n";
    cout << "-------------------------\n";
    for(int i = 0; i < limit; i++) {
        cout << list[i].roll_no << "\t" << list[i].name << "\t" << list[i].SGPA << "\n";
    }
}

int main() {
    int n;
    cout << "How many students do you want to enter? ";
    cin >> n;

    if(n <= 0) {
        cout << "Invalid number of students.\n";
        return 0;
    }

    student data[n]; // dynamic size array based on user input
    accept(data, n);

    int choice;
    while(true) {
        cout << "\nMenu:\n";
        cout << "1. Bubble Sort by Roll No\n";
        cout << "2. Insertion Sort by Roll No\n";
        cout << "3. Quick Sort by Roll No\n";
        cout << "4. Search by SGPA\n";
        cout << "5. Binary Search by Name\n";
        cout << "6. Top 10 Students by SGPA\n";
        cout << "7. Display All Students\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch(choice) {
            case 1: bubble_sort(data, n); display(data, n); break;
            case 2: insert_sort(data, n); display(data, n); break;
            case 3: quick_sort(data, 0, n-1); display(data, n); break;
            case 4: search(data, n); break;
            case 5: binary_search(data, n); break;
            case 6: top_students(data, n); break;
            case 7: display(data, n); break;
            case 8: cout << "Exiting program.\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
