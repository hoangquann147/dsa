// LAB 2 - PROBLEM 3: POSTFIX TO INFIX
#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 1. Recognize an operator.
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// 2. Convert each pair of operands into a parenthesized expression.
string postfixToInfix(const string& postfix) {
    stack<string> st;
    for (char c : postfix) {
        if (c == ' ' || (c >= '\t' && c <= '\r')) continue;
        if (isOperator(c)) {
            if (st.size() < 2) return "";
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();
            st.push("(" + op1 + c + op2 + ")");
        } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                   (c >= '0' && c <= '9')) {
            st.push(string(1, c));
        } else return "";
    }
    if (st.size() != 1) return "";
    return st.top();
}

// 3. Read one expression per line.
int main() {
    string s;
    while (getline(cin, s)) {
        string result = postfixToInfix(s);
        if (result.empty()) {
            cerr << "Error: invalid postfix expression\n";
            return 1;
        }
        cout << result << '\n';
    }
    return 0;
}
