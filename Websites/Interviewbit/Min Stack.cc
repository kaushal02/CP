/*
https://www.interviewbit.com/problems/min-stack/
*/
stack<int> S1, S2;

MinStack::MinStack() {
    while (!S1.empty()) S1.pop();
    while (!S2.empty()) S2.pop();
}

void MinStack::push(int x) {
    S1.push(x);
    if (S2.empty() or S2.top() >= x) S2.push(x);
}

void MinStack::pop() {
    if (S1.empty()) return;
    if (!S2.empty() and S2.top() == S1.top()) S2.pop();
    S1.pop();
}

int MinStack::top() {
    return (S1.empty() ? -1 : S1.top());
}

int MinStack::getMin() {
    return (S2.empty() ? -1 : S2.top());
}

