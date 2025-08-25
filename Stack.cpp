// Problem Statement: 
/*
Implement stack as an abstract data type using singly linked list and use this ADT for conversion of  
infix expression to postfix, prefix and evaluation of postfix and prefix expression.
*/

#include <iostream>
using namespace std;

class Node {
public:
    char data;
    Node *next;

    Node(char val) {
        data = val;
        next = NULL;
    }
};

class Stack {
private:
    Node *top;

public:
    Stack() {
        top = NULL;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void push(char x) {
        Node *temp = new Node(x);
        temp->next = top;
        top = temp;
    }

    char pop() {
        if (isEmpty()) {
            cout << "Error: Stack is empty." << endl;
            exit(1);
        }
        Node *temp = top;
        char x = temp->data;
        top = top->next;
        delete temp;
        return x;
    }

    char topData() {
        if (isEmpty()) {
            cerr << "Error: Stack is empty." << endl;
            exit(1);
        }
        return top->data;
    }
};

class Expression {
public:
    int precedence(char x);
    void reverse(char *a, char *b);
    int evaluate(int op1, int op2, char op);

    void infixToPostfix(char *infix, char *postfix);
    void infixToPrefix(char *infix, char *prefix);

    void evaluatePostfix(char *postfix);
    void evaluatePrefix(char *prefix);
};

int Expression::precedence(char x) {
    if (x == '(') return 0;
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 2;
    if (x == '^') return 3;
    return 4;
}

int Expression::evaluate(int op1, int op2, char op) {
    if (op == '+') return op1 + op2;
    if (op == '-') return op1 - op2;
    if (op == '*') return op1 * op2;
    if (op == '/') return op1 / op2;
    if (op == '%') return op1 % op2;
    return 0;
}

void Expression::reverse(char *a, char *b) {
    int i = 0, j = 0;
    while (a[i] != '\0') i++;
    i--;
    while (i >= 0) {
        if (a[i] == '(') b[j] = ')';
        else if (a[i] == ')') b[j] = '(';
        else b[j] = a[i];
        i--;
        j++;
    }
    b[j] = '\0';
}

void Expression::infixToPostfix(char *infix, char *postfix) {
    Stack s;
    int i = 0, j = 0;
    char token, x;

    while (infix[i] != '\0') {
        token = infix[i];
        if (isalnum(token)) {
            postfix[j++] = token;
        } else {
            if (token == '(')
                s.push(token);
            else if (token == ')') {
                while ((x = s.pop()) != '(') {
                    postfix[j++] = x;
                }
            } else {
                while (!s.isEmpty() && precedence(token) <= precedence(s.topData())) {
                    postfix[j++] = s.pop();
                }
                s.push(token);
            }
        }
        i++;
    }

    while (!s.isEmpty()) {
        postfix[j++] = s.pop();
    }
    postfix[j] = '\0';
}

void Expression::infixToPrefix(char *infix, char *prefix) {
    char prefix1[20], infix1[20];
    reverse(infix, infix1);
    infixToPostfix(infix1, prefix1);
    reverse(prefix1, prefix);
}

void Expression::evaluatePostfix(char *postfix) {
    Stack s;
    int i, op1, op2, result, x;
    char token;

    for (i = 0; postfix[i] != '\0'; i++) {
        token = postfix[i];
        if (isalnum(token)) {
            cout << "Enter value for " << token << ": ";
            cin >> x;
            s.push(char(x));
        } else {
            op2 = s.pop();
            op1 = s.pop();
            result = evaluate(op1, op2, token);
            s.push(char(result));
        }
    }

    result = s.pop();
    cout << "Result = " << result << endl;
}

void Expression::evaluatePrefix(char *prefix) {
    Stack s;
    int i = 0, op1, op2, result, x;
    char token;

    while (prefix[i] != '\0') i++;
    i--;

    while (i >= 0) {
        token = prefix[i];
        if (isalnum(token)) {
            cout << "Enter value for " << token << ": ";
            cin >> x;
            s.push(char(x));
        } else {
            op1 = s.pop();
            op2 = s.pop();
            result = evaluate(op1, op2, token);
            s.push(char(result));
        }
        i--;
    }

    result = s.pop();
    cout << "Result = " << result << endl;
}

int main() {
    Expression exp;
    char infix[20], postfix[20], prefix[20];
    int choice;

    do {
        cout << "\n1. Infix to Postfix Conversion";
        cout << "\n2. Infix to Prefix Conversion";
        cout << "\n3. Evaluate Postfix Expression";
        cout << "\n4. Evaluate Prefix Expression";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter Infix expression: ";
            cin >> infix;
            exp.infixToPostfix(infix, postfix);
            cout << "Postfix: " << postfix << endl;
            break;
        case 2:
            cout << "\nEnter Infix expression: ";
            cin >> infix;
            exp.infixToPrefix(infix, prefix);
            cout << "Prefix: " << prefix << endl;
            break;
        case 3:
            exp.evaluatePostfix(postfix);
            break;
        case 4:
            exp.evaluatePrefix(prefix);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cerr << "Wrong choice!" << endl;
        }
    } while (choice != 5);
}
