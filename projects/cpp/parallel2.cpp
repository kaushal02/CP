#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

mutex mtx;
condition_variable cv;

queue<int> q;

void producer(int id) {
    this_thread::sleep_for(chrono::seconds(2));

    lock_guard<mutex> lock(mtx);

    q.push(id);
    cout << "Pushed " << id << " to the shared queue.\n";

    cv.notify_one();
}

void consumer(int id, int times) {
    while (times--) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return !q.empty();});

        int val = q.front();
        q.pop();
        cout << "Consumer " << id << " popped " << val << " from the shared queue.\n";
    }
}

int main() {
    int factor = 2046;
    int nConsumers = 4;
    vector<thread*> consumers(nConsumers);
    for (int i = 0; i < nConsumers; i++) {
        consumers[i] = new thread(consumer, i + 1, factor);
    }

    int nProducers = factor * nConsumers;
    vector<thread*> producers(nProducers);
    for (int i = 0; i < nProducers; i++) {
        producers[i] = new thread(producer, i + 1);
    }

    for (int i = 0; i < nConsumers; i++) {
        consumers[i]->join();
    }
    for (int i = 0; i < nProducers; i++) {
        producers[i]->join();
    }
    return 0;
}