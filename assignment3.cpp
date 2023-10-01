# include <thread>
# include <mutex>
# include <chrono>

int x{0};
 
/*
It's possible that non of the threads can exit the loop:
thr1 acquire x and checks that x == 0
thr2 acquire x and checks that x == 0
thr1 computes x = 1 - x, resulting in x = 1
thr2 computes x = 1 - x, resulting in x = 0 
...
*/

/*
solution: lock the mutex when a thread acquires x
*/

std::mutex mtx;

void func() {
    std::lock_guard<std::mutex> lck(mtx);
    while (x == 0) {
        x = 1 - x;
    }
}
 
int main() {

        std::thread thr1{ func };
        std::thread thr2{ func };

        thr1.join();
        thr2.join();


    return 0;
}

