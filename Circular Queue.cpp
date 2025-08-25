//Problem Statement:
 /*
 Implement Circular Queue using Array. Perform following operations on it.
 a) Insertion (Enqueue)
 b) Deletion (Dequeue)
 c) Display
 */



#include <iostream>
using namespace std;

class CircularQueue {
    int queue[5];
    int n;
    int front, rear;

public:
    CircularQueue() {
        n = 5;
        front = -1;
        rear = -1;
        for (int i = 0; i < n; i++)
            queue[i] = 0;
    }

    bool is_empty() {
        return (front == -1 && rear == -1);
    }

    bool is_full() {
        return ((rear + 1) % n == front);
    }

    void enqueue(int no) {
        if (is_full()) {
            cout << "Queue full" << endl;
            return;
        }
        if (is_empty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % n;
        }
        queue[rear] = no;
        cout << "Enqueued: " << no << endl;
    }

    void dequeue() {
        if (is_empty()) {
            cout << "Queue empty" << endl;
            return;
        }
        cout << "Deleted: " << queue[front] << endl;
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % n;
        }
    }

    void display() {
        if (is_empty()) {
            cout << "Queue empty" << endl;
            return;
        }
        cout << "Queue: ";
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % n;
        }
        cout << endl;
    }
};

int main() {
    CircularQueue cq;
    int choice, no, count;

    while (true) {
        cout << "\nCircular Queue Menu:\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "How many numbers do you want to enqueue? ";
                cin >> count;
                for (int i = 0; i < count; i++) {
                    cout << "Enter number " << (i + 1) << ": ";
                    cin >> no;
                    cq.enqueue(no);
                }
                break;

            case 2:
                cq.dequeue();
                break;

            case 3:
                cq.display();
                break;

            case 4:
                cout << "Exiting program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
