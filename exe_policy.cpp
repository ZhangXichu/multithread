#include "include/exe_policy.h"

int main() {
    
    std::vector<int> vec(20000);

    std::iota(vec.begin(), vec.end(), 1);

    std::for_each(std::execution::par, vec.begin(), vec.end(),
        [](int x) {
            std::cout << x << " ";
        });
    std::cout << std::endl;

    return 0;
}