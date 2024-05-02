#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <set>
#include <chrono>
using namespace std;

class Scheduler {
    int n;
    mutex mtx;
    condition_variable cv;
    set<int> freeRooms;

    bool evict;
  public:
    Scheduler(int n_): n(n_) {
        for (int i = 1; i <= n; i++) {
            freeRooms.insert(i);
        }
    }
    void startAlarm() {
        lock_guard<mutex> lock(mtx);
        evict = true;
        for (int i = 1; i <= n; i++) {
            if (!freeRooms.count(i)) {
                freeRooms.insert(i);
            }
        }
        cv.notify_all();
    }
    void stopAlarm() {
        lock_guard<mutex> lock(mtx);
        evict = false;
        cv.notify_all();
    }
    int book(int timeoutInSeconds) {
        unique_lock<mutex> lock(mtx);
        cv.wait_until(lock, std::chrono::steady_clock::now() + chrono::seconds(timeoutInSeconds),
            [this]{ return !freeRooms.empty() && !evict; });
        if (evict || freeRooms.empty()) {
            return -1-evict;
        }
        int room = *freeRooms.begin();
        freeRooms.erase(room);
        return room;
    }
    void free(int roomNo) {
        {
            lock_guard<mutex> lock(mtx);
            freeRooms.insert(roomNo);
        }
        cv.notify_one();
    }
};

int main() {
    Scheduler s(5);
    int numClients = 20;

    vector<thread*> client(numClients);
    for (int i = 0; i < numClients; i++) {
        client[i] = new thread([i, &s]() {
            int roomNo = s.book(5);
            if (roomNo == -2) {
                string log = to_string(i) + ": Fire alarm is active\n";
                cout << log;
                return;
            }
            if (roomNo == -1) {
                string log = to_string(i) + ": No free rooms available\n";
                cout << log;
                return;
            }
            string log = to_string(i) + ": Booked room#" + to_string(roomNo) + "\n";
            cout << log;
            this_thread::sleep_for(chrono::seconds(2));
            s.free(roomNo);
            log = to_string(i) + ": Freed room#" + to_string(roomNo) + "\n";
            cout << log;
        });
    }
    thread start_alarm([&s]() {
        this_thread::sleep_for(chrono::milliseconds(2100));
        cout << "Ringing the fire alarm\n";
        s.startAlarm();
    });
    thread stop_alarm([&s]() {
        this_thread::sleep_for(chrono::milliseconds(4100));
        cout << "Stopping the fire alarm\n";
        s.stopAlarm();
    });

    for (int i = 0; i < numClients; i++) {
        client[i]->join();
    }
    start_alarm.join();
    stop_alarm.join();

    return 0;
}