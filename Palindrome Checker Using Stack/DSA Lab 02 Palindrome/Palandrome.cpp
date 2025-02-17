#include <iostream>
#include <stack>
#include <string>
using namespace std;

class PalindromeChecker {
public:
    bool isPalindrome(string str) {
        stack<char> s;
        int len = str.length();

        // Push all characters of the string into the stack
        for (int i = 0; i < len; i++) {
            s.push(str[i]);
        }

        // Pop characters from the stack and compare with the original string
        for (int i = 0; i < len; i++) {
            if (s.top() != str[i]) {
                return false; // If mismatch, it's not a palindrome
            }
            s.pop();
        }

        return true; // If all characters match, it's a palindrome
    }
};

int main() {
    PalindromeChecker checker;
    string str;
    cout << "Enter a string: ";
    cin >> str;

    if (checker.isPalindrome(str)) {
        cout << str << " is a palindrome" << endl;
    }
    else {
        cout << str << " is not a palindrome" << endl;
    }

    return 0;
}