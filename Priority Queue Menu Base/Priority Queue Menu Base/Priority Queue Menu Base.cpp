#include<iostream>
#include<iomanip> // for setw() which is used to set width of the output 
using namespace std;

int arr_size;

template<class T> // Template class for queue
class queue {
private:
    int front, rear, count;
    T* array;
public:
    queue() {
        front = rear = -1;
        array = new T[arr_size];
        count = 0;
    }

    bool isEmpty() {
        return (front > rear || front == -1);
    }

    bool isFull() {
        return (rear == arr_size - 1);
    }

    void Push(T value) {
        if (!isFull()) {
            if (front == -1)
                front = 0;
            rear++;
            array[rear] = value;
            count++;
        }
        else {
            cout << "Queue Overflow!" << endl;
        }
    }

    T pop() {
        T val;
        if (!isEmpty()) {
            val = array[front];
            front++;
            return val;
        }
        else {
            cout << "Queue Underflow!" << endl;
        }
        return "";
    }

    int getCount() {
        return count;
    }
};

void printMenu() {
    cout << "======================================" << endl;
    cout << setw(25) << " PERSON SELECTION MENU" << endl;
    cout << "======================================" << endl;
    cout << "1) Admin" << endl;
    cout << "2) Faculty" << endl;
    cout << "3) Student" << endl;
    cout << "======================================" << endl;
}

int main() {
    unsigned int size, choice;
    string value, admin_name, fac_name, stud_name;

    // Input validation for size
    cout << "Enter number of persons in queue: ";
    while (true) {
        cin >> size;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer: ";
        }
        else {
            break;
        }
    }
    arr_size = size;

    queue<string> Admin;
    queue<string> Faculty;
    queue<string> Student;
    queue<string> priority_queue;

    // Collecting input for each person
    for (int i = 1; i <= size; i++) {
        do {
            printMenu();
            cout << "Select the person who entered queue at position " << i << ": ";
            while (true) {
                cin >> choice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid integer: ";
                }
                else {
                    break;
                }
            }

            if (choice == 1) {
                cout << "Enter Admin Name: ";
                cin >> admin_name;
                Admin.Push(admin_name);
            }
            else if (choice == 2) {
                cout << "Enter Faculty Name: ";
                cin >> fac_name;
                Faculty.Push(fac_name);
            }
            else if (choice == 3) {
                cout << "Enter Student Name: ";
                cin >> stud_name;
                Student.Push(stud_name);
            }
            else {
                cout << "Invalid choice. Please choose between 1, 2, or 3." << endl;
            }
        } while (choice != 1 && choice != 2 && choice != 3);
    }

    // Moving persons into priority queue
    for (int i = 0; i < Admin.getCount(); i++) {
        value = Admin.pop();
        priority_queue.Push(value);
    }

    for (int i = 0; i < Faculty.getCount(); i++) {
        value = Faculty.pop();
        priority_queue.Push(value);
    }

    for (int i = 0; i < Student.getCount(); i++) {
        value = Student.pop();
        priority_queue.Push(value);
    }

    // Display the final priority queue
    cout << "\nPriority Queue: { ";
    for (int i = 0; i < priority_queue.getCount(); i++) {
        cout << priority_queue.pop() << " ";
    }
    cout << "}" << endl;

    return 0;
}
