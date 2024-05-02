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
    cv.notify_one();
}

void consumer(int id, int times, int& total) {
    total = 0;
    while (times--) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{return !q.empty();});
        total += q.front();
        q.pop();
    }
}

int main() {
    vector<thread*> producers(100);
    vector<thread*> consumers(20);
    vector<int> totals(20, 0);
    for (int i = 0; i < 20; i++) {
        consumers[i] = new thread(consumer, i, 5, std::ref(totals[i]));
    }
    for (int i = 0; i < 100; i++) {
        producers[i] = new thread(producer, i + 1);
    }
    for (int i = 0; i < 20; i++) {
        consumers[i]->join();
    }
    for (int i = 0; i < 100; i++) {
        producers[i]->join();
    }
    int sum = 0;
    for (int i = 0; i < 20; i++) {
        cout << totals[i] << " ";
        if (i % 5 == 4) {
            cout << endl;
        }
        sum += totals[i];
    }
    cout << sum << endl;
    return 0;
}