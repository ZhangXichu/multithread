# include <iostream>
# include <thread>

int g = 0;

void inc_num() {
    for (int i=0; i < 100000; i++) {
        g += 1;
    }
}

int main() {

    std::thread t1(inc_num);
    std::thread t2(inc_num);
    std::thread t3(inc_num);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "g = " << g << std::endl;

    return 0;

}