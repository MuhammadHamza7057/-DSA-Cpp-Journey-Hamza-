#include <iostream>
#include <limits>
using namespace std;

// Node structure to represent each element in the queue
struct Node {
    int data;
    Node* next;
};

// Dynamic Queue class to handle queue operations
class DynamicQueue {
private:
    Node* front;  // Front of the queue
    Node* rear;   // Rear of the queue

public:
    // Constructor to initialize an empty queue
    DynamicQueue() : front(nullptr), rear(nullptr) {}

    // Destructor to release allocated memory
    ~DynamicQueue() {
        while (!isEmpty()) {
            dequeue(); // Clean up memory by dequeuing all elements
        }
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return front == nullptr;
    }

    // Add an element to the rear of the queue
    void enqueue(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Enqueued: " << value << endl;
    }

    // Remove an element from the front of the queue
    void dequeue() {
        if (isEmpty()) {
            cout << "Error: Queue is empty. Cannot dequeue.\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;

        // If the queue becomes empty, reset rear to null
        if (front == nullptr) {
            rear = nullptr;
        }
        cout << "Dequeued successfully.\n";
    }

    // Get the element at the front of the queue
    int getFront() const {
        if (isEmpty()) {
            cout << "Error: Queue is empty." << endl;
            return 0;  // Return 0 as a neutral value, indicating the queue is empty
        }
        return front->data;
    }

    // Display all elements in the queue
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        Node* temp = front;
        cout << "Queue elements: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Function to get valid integer input from the user
int getValidInput() {
    int num;
    while (true) {
        cout << "Enter a number: ";
        cin >> num;

        // Validate input
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
        }
        else {
            return num;
        }
    }
}

// Main function to interact with the dynamic queue
int main() {
    DynamicQueue queue;
    int choice, value;

    while (true) {
        // Display menu options
        cout << "\n=============================\n";
        cout << "          QUEUE MENU         \n";
        cout << "=============================\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Display Queue\n";
        cout << "4. Get Front Element\n";
        cout << "5. Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        // Validate menu choice
        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a valid option (1-5).\n";
            continue;
        }

        // Handle menu choices
        switch (choice) {
        case 1:
            value = getValidInput(); // Get valid input for enqueue operation
            queue.enqueue(value);
            break;
        case 2:
            queue.dequeue();
            break;
        case 3:
            queue.display();
            break;
        case 4:
            cout << "Front element: " << queue.getFront() << endl;
            break;
        case 5:
            cout << "Exiting program. Goodbye!\n";
            return 0;
        }
    }
}