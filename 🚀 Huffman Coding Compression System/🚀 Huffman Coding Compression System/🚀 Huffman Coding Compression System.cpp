#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Compare function for priority queue (Min-Heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to generate Huffman Codes recursively
void generateHuffmanCodes(Node* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    // If it's a leaf node, store the Huffman code
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to build Huffman Tree
Node* buildHuffmanTree(const string& text, unordered_map<char, string>& huffmanCodes) {
    // Frequency Table
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Min-Heap Priority Queue
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Insert all characters into the priority queue
    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Create a new internal node
        Node* internalNode = new Node('\0', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    // Generate Huffman Codes
    Node* root = pq.top();
    generateHuffmanCodes(root, "", huffmanCodes);

    return root;
}

// Function to encode a string using Huffman Codes
string encode(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCodes.at(ch);
    }
    return encodedStr;
}

// Function to decode an encoded string
string decode(const string& encodedStr, Node* root) {
    string decodedStr = "";
    Node* current = root;

    for (char bit : encodedStr) {
        current = (bit == '0') ? current->left : current->right;

        // If it's a leaf node, append the character
        if (!current->left && !current->right) {
            decodedStr += current->ch;
            current = root;
        }
    }

    return decodedStr;
}

// Function to validate user input
int getValidChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation
        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "❌ Invalid input! Please enter a valid number (1-4)." << endl;
            continue;
        }
        return choice;
    }
}

// Function to display the menu
void displayMenu() {
    cout << "\n=========================================\n";
    cout << "  🚀 Huffman Coding Compression System  \n";
    cout << "=========================================\n";
    cout << "1️⃣  Enter a string for compression\n";
    cout << "2️⃣  View Huffman Codes\n";
    cout << "3️⃣  Decode the encoded string\n";
    cout << "4️⃣  Exit\n";
    cout << "=========================================\n";
}

int main() {
    string text, encodedStr, decodedStr;
    unordered_map<char, string> huffmanCodes;
    Node* root = nullptr;
    bool isEncoded = false;

    while (true) {
        displayMenu();
        int choice = getValidChoice();

        switch (choice) {
        case 1: {
            cout << "\n🔹 Enter a string to compress: ";
            cin.ignore();
            getline(cin, text);

            if (text.empty()) {
                cout << "❌ Error: Input string cannot be empty!\n";
                continue;
            }

            root = buildHuffmanTree(text, huffmanCodes);
            encodedStr = encode(text, huffmanCodes);
            isEncoded = true;

            cout << "\n✅ Compression Successful!";
            cout << "\n📄 Original String: " << text;
            cout << "\n🔢 Encoded String: " << encodedStr << endl;
            break;
        }

        case 2: {
            if (!isEncoded) {
                cout << "❌ Error: No data encoded yet! Please enter a string first.\n";
                continue;
            }

            cout << "\n📌 Huffman Codes:";
            cout << "\nCharacter | Huffman Code\n";
            cout << "------------------------\n";
            for (auto& pair : huffmanCodes) {
                cout << "    " << pair.first << "      |     " << pair.second << endl;
            }
            break;
        }

        case 3: {
            if (!isEncoded) {
                cout << "❌ Error: No encoded data to decode! Please encode first.\n";
                continue;
            }

            decodedStr = decode(encodedStr, root);

            cout << "\n🔍 Decoded String: " << decodedStr << endl;
            if (decodedStr == text) {
                cout << "✅ Decoding Successful! The decoded text matches the original.\n";
            }
            else {
                cout << "⚠️ Decoding Error: The decoded text does not match the original.\n";
            }
            break;
        }

        case 4:
            cout << "🔚 Exiting program... Thank you for using Huffman Coding Compression System! 🚀\n";
            return 0;

        default:
            cout << "❌ Invalid choice! Please select a valid option.\n";
        }
    }

    return 0;
}
