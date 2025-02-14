#include <iostream>
#include <stack>

using namespace std;

class Stack {
private:

    //stacks to store elements

    stack<int> MainStack;
    stack<int> MinStack;

public:

    void push(int value) {
        MainStack.push(value);

        //checking the value if its small than push it to MinStack as well
        if (MinStack.empty() || value <= MinStack.top()) {
            MinStack.push(value);
        }

        cout << "Pushed " << value << " onto the stack." << endl;
    }


    void pop() {
        if (MainStack.empty()) {
            cout << "Stack is empty! Cannot pop." << endl;
            return;
        }

        int poppedValue = MainStack.top();
        //remove it from both stacks 
        if (MainStack.top() == MinStack.top()) {
            MinStack.pop();
        }
        MainStack.pop();


        cout << "Popped " << poppedValue << " from the stack." << endl;
    }


    void getMin() {
        if (MinStack.empty()) {
            cout << "Stack is empty, no minimum element!" << endl;
        }
        else {
            cout << "Current Minimum: " << MinStack.top() << endl;
        }
    }


    void size() {
        cout << "Stack Size: " << MainStack.size() << endl;
    }
};

int main() {
    Stack s;
    int choice, value;

    while (true) {
        cout << "\n\n****************************************\n";
        cout << "1. Push Element\n2. Pop Element\n3. Get Minimum\n4. Get Stack Size\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // handling non numaric inputs
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> value;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a valid integer." << endl;
                continue;
            }

            s.push(value);
            break;
        case 2:
            s.pop();
            break;
        case 3:
            s.getMin();
            break;
        case 4:
            s.size();
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    }

    return 0;
}