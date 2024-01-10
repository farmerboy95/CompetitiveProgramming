#include <stack>

bool delim(char c) {
    return c == ' ';
}

bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return -1;
}

void processOp(stack<int>& st, char op) {
    int r = st.top(); st.pop();
    int l = st.top(); st.pop();
    switch (op) {
        case '+': st.push(l + r); break;
        case '-': st.push(l - r); break;
        case '*': st.push(l * r); break;
        case '/': st.push(l / r); break;
    }
}

int evaluate(string& s) {
    stack<int> st;
    stack<char> op;
    for (int i = 0; i < (int) s.size(); i++) {
        if (delim(s[i])) {
            continue;
        }
        
        if (s[i] == '(') {
            op.push('(');
        } else if (s[i] == ')') {
            while (op.top() != '(') {
                processOp(st, op.top());
                op.pop();
            }
            op.pop();
        } else if (isOp(s[i])) {
            char curOp = s[i];
            while (!op.empty() && priority(op.top()) >= priority(curOp)) {
                processOp(st, op.top());
                op.pop();
            }
            op.push(curOp);
        } else {
            int number = 0;
            while (i < (int)s.size() && isalnum(s[i])) {
                number = number * 10 + s[i++] - '0';
            }
            --i;
            st.push(number);
        }
    }

    while (!op.empty()) {
        processOp(st, op.top());
        op.pop();
    }
    return st.top();
}