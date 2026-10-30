#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
using namespace std;

bool isNumber(const string &t) {
    if (t.empty()) return false;
    size_t i = 0;
    if (t[0] == '-') {
        if (t.size() == 1) return false;
        i = 1;
    }
    for (; i < t.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(t[i]))) return false;
    }
    return true;
}

int precedence(const string &op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// Equal precedence pops for + - * /. ^ stays, so 2 ^ 3 ^ 2 is 2 ^ (3 ^ 2).
bool popFirst(const string &top, const string &incoming) {
    if (incoming == "^") return precedence(top) > precedence(incoming);
    return precedence(top) >= precedence(incoming);
}

int apply(int a, const string &op, int b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        int q = a / b;
        if (a % b != 0 && ((a < 0) != (b < 0))) q--;
        return q;
    }
    int r = 1;
    for (int i = 0; i < b; i++) r *= a;
    return r;
}

string stackText(const vector<int> &v) {
    string s = "[";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) s += " ";
        s += to_string(v[i]);
    }
    return s + "]";
}

string stackText(const vector<string> &v) {
    string s = "[";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) s += " ";
        s += v[i];
    }
    return s + "]";
}

void show(const string &tok, const vector<int> &values, const vector<string> &ops,
          const string &action) {
    cout << left << setw(8) << tok
         << setw(18) << stackText(values)
         << setw(14) << stackText(ops)
         << action << endl;
}

void reduce(vector<int> &values, vector<string> &ops, bool trace) {
    int b = values.back();
    values.pop_back();
    int a = values.back();
    values.pop_back();
    string op = ops.back();
    ops.pop_back();
    int r = apply(a, op, b);
    values.push_back(r);
    if (trace)
        show("", values, ops, to_string(a) + " " + op + " " + to_string(b) + " = " + to_string(r));
}

int evaluate(const vector<string> &tokens, bool trace) {
    vector<int> values;
    vector<string> ops;

    for (const string &tok : tokens) {
        if (isNumber(tok)) {
            values.push_back(stoi(tok));
        } else {
            while (!ops.empty() && popFirst(ops.back(), tok))
                reduce(values, ops, trace);
            ops.push_back(tok);
        }
        if (trace) show(tok, values, ops, "");
    }

    if (trace) cout << endl << "remaining" << endl;
    while (!ops.empty())
        reduce(values, ops, trace);
    return values.back();
}

void run(const vector<string> &expr) {
    for (int i = 0; i < (int)expr.size(); i++) {
        if (i) cout << " ";
        cout << expr[i];
    }
    cout << endl << endl;
    cout << left << setw(8) << "token" << setw(18) << "values" << setw(14)
         << "operators" << "action" << endl;
    int result = evaluate(expr, true);
    cout << "result: " << result << endl << endl;
}

int main() {
    run({"8", "+", "3", "*", "2", "^", "2", "-", "20", "/", "4"});
    run({"2", "^", "3", "^", "2"});
    run({"-7", "/", "2"});
    return 0;
}
