#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <cmath>

using namespace std;

// Function to perform arithmetic operations
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) return a / b;
            else {
                cout << "Error: Division by zero!" << endl;
                exit(1);
            }
        default: 
            cout << "Error: Unsupported operation!" << endl;
            exit(1);
    }
}

// Function to evaluate the expression
double evaluateExpression(const string& expression) {
    stack<double> values; // Stack to store numbers
    stack<char> ops;      // Stack to store operators

    for (int i = 0; i < expression.size(); i++) {
        // Skip spaces
        if (expression[i] == ' ') continue;

        // If it's a number, push it to the value stack
        if (isdigit(expression[i])) {
            double value = 0;
            // Parse the number (could be more than one digit)
            while (i < expression.size() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            values.push(value);
            i--; // Decrease to correct the loop index
        }
        // If it's an operator, process it
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (!ops.empty() && (ops.top() == '*' || ops.top() == '/' || (ops.top() == '+' || ops.top() == '-') )) {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    // Process remaining operators
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();
        double val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOperation(val1, val2, op));
    }

    // The result is the only value left in the stack
    return values.top();
}

int main() {
    string expression;
    cout << "Enter a mathematical expression (e.g., 3+5*2-4/2): ";
    getline(cin, expression);

    // Evaluate and display the result
    double result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}
