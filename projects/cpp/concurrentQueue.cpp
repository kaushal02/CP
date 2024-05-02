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
        }
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
        return true;
    }
    void wait_and_pop(Data& value) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]{ return !q.empty(); });
        value = q.front();
        q.pop();
    }
    void addLogLine(string data) {
        log.addLine(data);
    }
    void printLogs() {
        log.print();
    }
};

void producer(int value, Queue<int>& q) {
    this_thread::sleep_for(chrono::seconds(2));
    q.addLogLine("Pushing " + to_string(value) + " to the queue");
    q.push(value);
    q.addLogLine("Pushed " + to_string(value) + " to the queue");
}

void consumer(int count, Queue<int>& q, int& total) {
    while (count--) {
        int value;
        q.wait_and_pop(value);
        q.addLogLine("Popped " + to_string(value) + " from the queue");
        total += value;
    }
}

int main() {
    Queue<int> q;
    int factor = 2;

    int nConsumers = 5;
    vector<int> totals(nConsumers);
    vector<thread*> consumers(nConsumers);
    for (int i = 0; i < nConsumers; i++) {
        consumers[i] = new thread(consumer, factor, std::ref(q), std::ref(totals[i]));
    }

    int nProducers = factor * nConsumers;
    vector<thread*> producers(nProducers);
    for (int i = 0; i < nProducers; i++) {
        producers[i] = new thread(producer, i + 1, std::ref(q));
    }

    for (int i = 0; i < nProducers; i++) {
        producers[i]->join();
    }
    int sum = 0;
    for (int i = 0; i < nConsumers; i++) {
        consumers[i]->join();
        sum += totals[i];
    }
    q.printLogs();
    cout << sum << endl;
    return 0;
}