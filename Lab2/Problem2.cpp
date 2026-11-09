#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOperand(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
           (ch >= '0' && ch <= '9');
}

int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

string infixToPostfix(const string& infix) {
    stack<char> operators;
    string result;
    bool expectOperand = true;
    for (unsigned char value : infix) {
        if (value == ' ' || (value >= '\t' && value <= '\r')) continue;
        const char ch = static_cast<char>(value);
        if (isOperand(ch)) {
            if (!expectOperand) return "";
            result += ch;
            expectOperand = false;
        } else if (ch == '(') {
            if (!expectOperand) return "";
            operators.push(ch);
        } else if (ch == ')') {
            if (expectOperand) return "";
            while (!operators.empty() && operators.top() != '(') {
                result += operators.top();
                operators.pop();
            }
            if (operators.empty()) return "";
            operators.pop();
        } else if (precedence(ch) != 0) {
            if (expectOperand) return "";
            // Equal-precedence ^ stays on the stack: exponentiation is right-associative.
            while (!operators.empty() && operators.top() != '(' &&
                   (precedence(operators.top()) > precedence(ch) ||
                    (precedence(operators.top()) == precedence(ch) && ch != '^'))) {
                result += operators.top();
                operators.pop();
            }
            operators.push(ch);
            expectOperand = true;
        } else {
            return "";
        }
    }
    if (expectOperand) return "";
    while (!operators.empty()) {
        if (operators.top() == '(') return "";
        result += operators.top();
        operators.pop();
    }
    return result;
}

// Read one expression per line until EOF.
int main() {
    string s;
    while (getline(cin, s)) {
        string result = infixToPostfix(s);
        if (result.empty()) {
            cerr << "Error: invalid infix expression\n";
            return 1;
        }
        cout << result << '\n';
    }
    return 0;
}
