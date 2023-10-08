# include <iostream>
# include <future>
# include <thread>


void add(int a, int b, std::promise<int> pros) {

    std::this_thread::sleep_for(std::chrono::seconds(2));
    pros.set_value(a + b);

    return;
}

int main() {

    std::promise<int> promise_add; 
    std::future<int> future_add = promise_add.get_future();

    std::thread thr_add(add, 6, 7, std::move(promise_add));

    std::cout << "Result is: " << future_add.get() << std::endl;

    thr_add.join();

    return 0;
}