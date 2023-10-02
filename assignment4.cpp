#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
// condition_variable cv;
bool writing_completed = false;
string sdata{"Empty"};

// Waiting thread
void reader() {
	unique_lock<std::mutex> guard(mut);            // Acquire lock

    while(!writing_completed) {
        guard.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        guard.lock();
    }
	           
    // Wake up and use the new value
    cout << "Data is " << sdata << endl;
}

// Modyifing thread
void writer() {
	cout << "Writing data..." << endl;
	{
		lock_guard<std::mutex> lg(mut);            // Acquire lock
        // set state to not complete
        writing_completed = false;
		std::this_thread::sleep_for(2s);           // Pretend to be busy...
		sdata = "Populated";                       // Modify the data
	}
	// Notify the condition variable
    writing_completed = true;
}

int main() {
	cout << "Data is " << sdata << endl;
	thread read{reader};
    thread write{writer};
	/*
	// If the writer thread finishes before the reader thread starts, the notification is lost
	thread write{writer};
	std::this_thread::sleep_for(500ms);
	thread read{reader};
	*/
	write.join();
	read.join();
}