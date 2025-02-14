#include<iostream>
#include<stack>
#include<string>
using namespace std;

string reverseword(string word) {
	stack<char>s;
	string reverseword = "";
	// loop for push the word to stack

	for (int i = 0; i < word.length(); i++)
	{
		s.push(word[i]);
	}

	// loop for pop the word from the stack

	for (int i = 0; i < word.length(); i++) {
		reverseword += s.top();
		s.pop();
	}
	return reverseword;
}
int main() {
	string word;
	cout << "Enter the word :";
	cin >> word;
	cout << "The reverse word is : " << reverseword(word) << endl;
	return 0;
}
