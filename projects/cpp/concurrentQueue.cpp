#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

class Log {
    mutex mtx;
    vector<string> data;
  public:
    Log() {}
    void addLine(string log) {
        lock_guard<mutex> lock(mtx);
        data.push_back(log);
    }
    void print() {
        for (string log: data) {
            cout << log << endl;
        }
    }
};

template <typename Data>
class Queue {
    mutex mtx;
    condition_variable cv;
    queue<Data> q;
    Log log;
  public:
    Queue() {}
    void push(const Data& data) {
        {
            lock_guard<mutex> lock(mtx);
            q.push(data);
            log.addLine("+" + to_string(data));
        } // lock is automatically released when it goes out of scope
        cv.notify_one();
    }
    bool empty() {
        lock_guard<mutex> lock(mtx);
        return q.empty();
    }
    bool try_pop(Data& value) {
        lock_guard<mutex> lock(mtx);
        if (q.empty()) {
            return false;
        }
        value = q.front();
        q.pop();
        log.addLine("-" + to_string(value));
        return true;
    }
    void wait_and_pop(Data& value) {
        unique_lock<mutex> lock(mtx);
        if (!cv.wait_until(
                lock, 
                std::chrono::steady_clock::now() + chrono::milliseconds(1500),
                [this]{ return !q.empty(); })) {
            throw runtime_error("Timeout waiting for queue item");
        }
        value = q.front();
        q.pop();
        log.addLine("-" + to_string(value));
    }
    void addLogLine(string data) {
        lock_guard<mutex> lock(mtx);
        log.addLine(data);
    }
    void printLogs() {
        log.print();
    }
};

void producer(int count, int value, Queue<int>& q) {
    value *= count;
    while (count--) {
        q.push(value++);
        this_thread::sleep_for(chrono::seconds(2));
    }
}

void consumer(int count, Queue<int>& q, vector<int>& totals, int index) {
    while (count > 0) {
        try {
            int value;
            q.wait_and_pop(value);
            totals[index] += value;
            count--;
        } catch (const runtime_error& e) {
            q.addLogLine("Error in consumer#" + to_string(index) + ": " + string(e.what()));
            continue;
        }
    }
}

int main() {
    Queue<int> q;
    int factor = 2;

    int nThreads = 4;

    vector<int> totals(nThreads, 0);

    vector<thread*> producers(nThreads);
    for (int i = 0; i < nThreads; i++) {
        producers[i] = new thread(producer, factor, i + 1, std::ref(q));
    }

    vector<thread*> consumers(nThreads);
    for (int i = 0; i < nThreads; i++) {
        consumers[i] = new thread(consumer, factor, std::ref(q), std::ref(totals), i);
    }

    for (int i = 0; i < nThreads; i++) {
        producers[i]->join();
    }

    int sum = 0;
    for (int i = 0; i < nThreads; i++) {
        consumers[i]->join();
        sum += totals[i];
    }
    cout << sum << endl;

    q.printLogs();
    return 0;
}
