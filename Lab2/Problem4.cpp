// LAB 2 - PROBLEM 4: PREFIX EVALUATION
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <vector>

using namespace std;

// 1. Read space-separated tokens from right to left.
bool evaluatePrefix(const string& prefix, double& result) {
    stringstream input(prefix);
    vector<string> tokens;
    string token;
    while (input >> token) tokens.push_back(token);
    stack<double> st;
    for (int i = static_cast<int>(tokens.size()) - 1; i >= 0; i--) {
        token = tokens[i];
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (st.size() < 2) return false;
            double a = st.top(); st.pop(); // Left operand first.
            double b = st.top(); st.pop();
            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else {
                if (b == 0) return false;
                st.push(a / b);
            }
        } else {
            stringstream number(token);
            double value;
            char extra;
            if (!(number >> value) || (number >> extra)) return false;
            st.push(value);
        }
    }
    if (st.size() != 1) return false;
    result = st.top();
    return true;
}

// 2. Evaluate one expression per line.
int main() {
    string s;
    cout.precision(15);
    while (getline(cin, s)) {
        double result;
        if (!evaluatePrefix(s, result)) {
            cerr << "Error: invalid expression or division by zero\n";
            return 1;
        }
        cout << result << '\n';
    }
    return 0;
}
