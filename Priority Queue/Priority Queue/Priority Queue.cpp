#include <iostream>
#include <vector>
#include <limits> // For numeric_limits
using namespace std;

// Priority Queue class
class PriorityQueue {
private:
    vector<int> heap;

    // Helper function to maintain heap property after insertion
    void heapifyUp(int index) {
        while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Helper function to maintain heap property after deletion
    void heapifyDown(int index) {
        int size = heap.size();
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Insert an element into the priority queue
    void enqueue(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Remove and return the highest priority element
    int dequeue() {
        if (heap.empty()) {
            cout << "Error: Queue is empty." << endl;
            return -1;  // Return a special value to indicate the queue is empty
        }
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return root;
    }

    // Get the element with the highest priority
    int getFront() const {
        if (heap.empty()) {
            cout << "Error: Queue is empty." << endl;
            return -1;
        }
        return heap[0];
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return heap.empty();
    }

    // Display the queue elements (for testing purposes)
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Priority Queue: ";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

// Function to handle input validation
int getValidatedInput() {
    int value;
    while (true) {
        cout << "Enter a number: ";
        cin >> value;

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a valid number." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input
            return value;
        }
    }
}

int main() {
    PriorityQueue pq;
    int choice;
    bool running = true;

    while (running) {
        cout << "=================================\n";
        cout << "\tPriority Menu:\n";
        cout << "=================================\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Get Front Element\n";
        cout << "4. Display Queue\n";
        cout << "5. Exit\n";
        cout << "=================================\n";
        cout << "Enter your choice: ";

        // Validate menu choice input
        while (!(cin >> choice)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid choice. Please select a valid option." << endl;
            cout << "Enter your choice: "; // Prompt again
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input

        switch (choice) {
        case 1: {
            int value = getValidatedInput();
            pq.enqueue(value);
            cout << "Added " << value << " to the queue." << endl;
            break;
        }
        case 2: {
            int front = pq.dequeue();
            if (front != -1) {
                cout << "Removed element: " << front << endl;
            }
            break;
        }
        case 3: {
            int front = pq.getFront();
            if (front != -1) {
                cout << "Front element: " << front << endl;
            }
            break;
        }
        case 4: {
            pq.display();
            break;
        }
        case 5:
            running = false;
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
