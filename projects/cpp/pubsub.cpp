#include <atomic>
#include <condition_variable>
#include <exception>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
using namespace std;

class SubscriberException: public exception {
    string subscriberName;
    string topicName;
    string message;
  public:
    SubscriberException(string s, string t, string msg):
        subscriberName(s), topicName(t), message(msg) {}
    string what() {
        return "Subscriber " + subscriberName + message + "Topic " + topicName;
    }
};
class AlreadySubscribedException: public SubscriberException {
  public:
    AlreadySubscribedException(string s, string t):
        SubscriberException(s, t, " already subscribed to ") {}
};
class NotSubscribedException: public SubscriberException {
  public:
    NotSubscribedException(string s, string t):
        SubscriberException(s, t, " not subscribed to ") {}
};

class Topic {
    string name;
    shared_mutex mtx;
    vector<string> messages; // length limit = 100, time expiry.

  public:
    Topic(string nm): name(nm) {}
    string getName() {
        return name;
    }
    void addMessage(string& message) {
        unique_lock lock(mtx);
        messages.push_back(message);
    }
    int numMessages() {
        shared_lock lock(mtx);
        return messages.size();
    }
    string getMessage(int k) {
        shared_lock lock(mtx);
        return (k < messages.size() ? messages[k] : "");
    }
};

class Subscriber {
    string name;
  public:
    Subscriber(string nm): name(nm) {}
    string getName() {
        return name;
    }
    void consume(string message) {
        string log = name + ".Consume(" + message + ")\n";
        cout << log;
        this_thread::sleep_for(chrono::seconds(2));
        log = name + ".ConsumeComplete(" + message + ")\n";
        cout << log;
    }
};

class SubscriberWorker {
    condition_variable cv;
    mutex mtx;
    bool run;

    Topic* topic;
    Subscriber* subscriber;
    atomic_int offset;
    thread thr;
  public:
    SubscriberWorker(Topic* t, Subscriber* s):
        topic(t), subscriber(s), offset(0), run(true),
        thr([this]() {
            unique_lock<mutex> lock(mtx);
            while (true) {
                cv.wait(lock, [this]{
                    return offset.load() < topic->numMessages() || !run;
                });
                int value = offset.load();
                if (value >= topic->numMessages() && !run) {
                    break;
                }
                subscriber->consume(topic->getMessage(value));
                offset.compare_exchange_weak(value, value + 1);
            }
        }) {}
    ~SubscriberWorker() {
        run = false;
        cv.notify_one();
        thr.join();
    }

    void wakeUp() {
        cv.notify_one();
    }
    void setOffset(int newOffset) {
        lock_guard<mutex> lock(mtx);
        offset = newOffset;
    }
};

class TopicHandler {
    Topic* topic;
    unordered_map<string, SubscriberWorker*> subscriberWorkers;
  public:
    TopicHandler(Topic* t): topic(t) {}
    ~TopicHandler() {
        for (auto& kv: subscriberWorkers) {
            delete kv.second;
        }
    }
    void subscribe(Subscriber* subscriber) {
        if (subscriberWorkers.find(subscriber->getName()) != subscriberWorkers.end()) {
            throw AlreadySubscribedException(subscriber->getName(), topic->getName());
        }
        SubscriberWorker* worker = new SubscriberWorker(topic, subscriber);
        subscriberWorkers[subscriber->getName()] = worker;
    }
    void publish() {
        for (auto& kv: subscriberWorkers) {
            kv.second->wakeUp();
        }
    }
    void resetOffset(Subscriber* subscriber, int newOffset) {
        if (subscriberWorkers.find(subscriber->getName()) == subscriberWorkers.end()) {
            throw NotSubscribedException(subscriber->getName(), topic->getName());
        }
        subscriberWorkers[subscriber->getName()]->setOffset(newOffset);
    }
};

class Queue {
    unordered_map<string, TopicHandler*> topicHandlers;
  public:
    Queue() {}
    ~Queue() {
        for (auto& kv: topicHandlers) {
            delete kv.second;
        }
    }
    Topic* createTopic(string name) {
        Topic* topic = new Topic(name);
        topicHandlers[name] = new TopicHandler(topic);
        string log = name + ".Created()\n";
        cout << log;
        return topic;
    }
    void publish(Topic* topic, string message) {
        string log = topic->getName() + ".Publish(" + message + ")\n";
        cout << log;
        topic->addMessage(message);
        topicHandlers[topic->getName()]->publish();
        log = topic->getName() + ".PublishComplete(" + message + ")\n";
        cout << log;
    }
    void subscribe(Topic* topic, Subscriber* subscriber) {
        try {
            string log = topic->getName() + ".Add(" + subscriber->getName() + ")\n";
            cout << log;
            topicHandlers[topic->getName()]->subscribe(subscriber);
            log = topic->getName() + ".AddComplete(" + subscriber->getName() + ")\n";
            cout << log;
        } catch (AlreadySubscribedException* e) {
            cout << e->what() << endl;
        }
    }
    void resetOffset(Topic* topic, Subscriber* subscriber, int newOffset) {
        try {
            string log = topic->getName() + ".Reset(" + subscriber->getName() +
                         ", " + to_string(newOffset) + ")\n";
            cout << log;
            topicHandlers[topic->getName()]->resetOffset(subscriber, newOffset);
            log = topic->getName() + ".ResetComplete(" + subscriber->getName() +
                  ", " + to_string(newOffset) + ")\n";
            cout << log;
        } catch (NotSubscribedException* e) {
            cout << e->what() << endl;
        }
    }
    void exit() {

    }
};

int main() {
    Queue q;
    Topic* t1 = q.createTopic("t1");
    Topic* t2 = q.createTopic("t2");

    Subscriber* s1 = new Subscriber("s1");
    Subscriber* s2 = new Subscriber("s2");
    Subscriber* s3 = new Subscriber("s3");

    q.publish(t1, "m1");

    q.subscribe(t1, s1);
    q.subscribe(t1, s2);
    q.subscribe(t2, s2);

    q.publish(t1, "m2");
    q.publish(t2, "m3");
    q.publish(t2, "m4");
    q.publish(t2, "m5");
    this_thread::sleep_for(chrono::seconds(5));
    q.resetOffset(t2, s2, 1);
    q.subscribe(t2, s3);
    q.publish(t2, "m6");
    return 0;
}
