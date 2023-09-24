# include <iostream>
# include <thread>

/**
 * @brief 
 * 
 * @param n laargest number in the game
 */
void fizzbuzz(int n) {
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0) {
            std::cout << "fizz!" << std::endl;
        } else if (i % 5 == 0) {
            std::cout << "buzz!" << std::endl;
        } else if (i % 15 == 0) {
            std::cout << "fizzbuzz" << std::endl;
        }
    }

}


int main() {


    int n = 35;
    std::thread thr(fizzbuzz, n);

    thr.join();

    return 0;
}