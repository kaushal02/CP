// C++ Program to illustrate the use of Condition Variables
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

// mutex to block threads
mutex mtx;
condition_variable cv;

// function to avoid spurios wakeup
bool data_ready = false;

// producer function working as sender
void producer()
{
	// Simulate data production
	this_thread::sleep_for(chrono::seconds(2));

	// lock release
	lock_guard<mutex> lock(mtx);

	// variable to avoid spurious wakeup
	data_ready = true;

	// logging notification to console
	cout << "Data Produced!" << endl;

	// notify consumer when done
	cv.notify_one();
}

// consumer that will consume what producer has produced
// working as reciever
void consumer()
{
	// locking
	unique_lock<mutex> lock(mtx);

	// waiting
	cv.wait(lock, [] { return data_ready; });

	cout << "Data consumed!" << endl;
}

// drive code
int main()
{
	thread consumer_thread(consumer);
	thread producer_thread(producer);

	consumer_thread.join();
	producer_thread.join();

    return 0;
}