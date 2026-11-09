// LAB 2 - PROBLEM 1: BALANCED BRACKETS
#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 1. Check a pair of brackets.
bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// 2. Match every closing bracket with the latest opening bracket.
bool isBalanced(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == ' ' || (c >= '\t' && c <= '\r')) continue;
        if (c == '(' || c == '{' || c == '[') st.push(c);
        else if (c == ')' || c == '}' || c == ']') {
            if (st.empty() || !isMatching(st.top(), c)) return false;
            st.pop();
        } else return false;
    }
    return st.empty();
}

// 3. Read one sequence per line until EOF.
int main() {
    string s;
    while (getline(cin, s))
        cout << (isBalanced(s) ? "Balanced" : "Not balanced") << '\n';
    return 0;
}
