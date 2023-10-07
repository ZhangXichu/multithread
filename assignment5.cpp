# include <mutex>
# include <atomic>
# include <iostream>
# include <thread>
# include <vector>

class some_type {
	// ...
public:
	void do_it() { /*...*/ 
        std::cout << "Function do_it() is called." << std::endl;
    }
};

// Variable to be lazily initialized
std::atomic<some_type*> ptr;
std::mutex process_mutex;

void process() {
    if (!ptr) {
        std::lock_guard<std::mutex> lk(process_mutex);

        if (!ptr) {
            ptr = new some_type;
        }
    }

    // copy to a non-atomic pointer
    some_type* ptr_n = ptr;
    ptr_n->do_it();

    // all the pointers in all the threads should
    // point to the same address
    std::cout << "ptr points to " << ptr << std::endl;   
    std::cout << "ptr_n points to " << ptr_n << std::endl;
}

int main() {

    std::vector<std::thread> threads;
	
	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread{process});
	for (auto&t : threads)
		t.join();

    delete ptr;

    return 0;
}